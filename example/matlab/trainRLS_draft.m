%% This function loads a 1*4096 YarpMonoImage, converts it into a matrix and 
% trains the classifier GURLS. 
% Author: Niklas Barkmeyer, 25.02.

%% YARP Port / Load Image
LoadYarp;
import yarp.BufferedPortImageFloat
port=BufferedPortImageFloat;
port_nr=BufferedPortImageFloat_nr;

disp('Registering port /matlab/read');
port.close; %make sure the port is closed, calling open twice hangs
port_nr.close;

port.open('/matlab/read');
port_nr.open('/matlab/read_nr');

%disp('Please connect the port /matlab/sink to an image source');
yarpImage=port.read;
h=yarpImage.height;
w=yarpImage.width;
%now we need to convert the yarpImage (a Java object) into a matlab matrix
tool=YarpImageHelper(h, w);

% Does this work?
TMP=tool.get2DMatrix(yarpImage);
%Does this work? 
TMP=tool.getMonoMatrix(yarpImage);

%% Load classnumber
classnr=prot_nr.read; % sonst genauso wie mit Image (aber 20000*1 und nicht 20000*4096)

%% RLS (batch)

name = [resdir '/standardRLSfixlambda']; 
optRLSfixlambda = gurls_defopt(name); 
optRLSfixlambda.newprop('paramsel.lambdas', opt.paramsel.lambdas*n0/ntr_tot); 
 
optRLSfixlambda.seq = {'rls:primal','pred:primal','perf:macroavg'}; 
optRLSfixlambda.process{1} = [2,0,0]; 
optRLSfixlambda.process{2} = [3,2,2]; 
optRLSfixlambda = gurls(Xtr_tot, ytr_tot, optRLSfixlambda,1); 
optRLSfixlambda = gurls(Xte, yte, optRLSfixlambda,2); 

port.close;
