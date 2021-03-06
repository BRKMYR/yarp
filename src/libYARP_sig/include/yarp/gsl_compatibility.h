// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

/*
* Copyright (C) 2007 RobotCub Consortium
* Authors: Lorenzo Natale
* CopyPolicy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT
*
*/

// $Id: gsl_compatibility.h,v 1.7 2007-03-27 15:10:45 babybot Exp $

/** 
* Defines types for binary compatibily with the GSL. Included by cpp 
* files within yarp.
*/

#ifndef gsl_block
typedef struct 
{
  size_t size;
  double *data;
} gsl_block;
#endif

#ifndef gsl_vector
struct gsl_vector
{
  size_t size;
  size_t stride;
  double *data; 
  gsl_block *block;
  int owner;
};
#endif

#ifndef gsl_matrix
struct gsl_matrix
{
  size_t size1;
  size_t size2;
  size_t tda;
  double * data;
  gsl_block * block;
  int owner;
};
#endif

//
