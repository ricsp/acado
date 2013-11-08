/*
 *    This file is part of ACADO Toolkit.
 *
 *    ACADO Toolkit -- A Toolkit for Automatic Control and Dynamic Optimization.
 *    Copyright (C) 2008-2009 by Boris Houska and Hans Joachim Ferreau, K.U.Leuven.
 *    Developed within the Optimization in Engineering Center (OPTEC) under
 *    supervision of Moritz Diehl. All rights reserved.
 *
 *    ACADO Toolkit is free software; you can redistribute it and/or
 *    modify it under the terms of the GNU Lesser General Public
 *    License as published by the Free Software Foundation; either
 *    version 3 of the License, or (at your option) any later version.
 *
 *    ACADO Toolkit is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *    Lesser General Public License for more details.
 *
 *    You should have received a copy of the GNU Lesser General Public
 *    License along with ACADO Toolkit; if not, write to the Free Software
 *    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 *
 */


/**
 *    \file include/acado/matrix_vector/vector.ipp
 *    \author Hans Joachim Ferreau, Boris Houska
 *    \date 31.05.2008
 */


//
// PUBLIC MEMBER FUNCTIONS:
//


BEGIN_NAMESPACE_ACADO



inline Vector Vector::operator+(	const Vector& arg
									) const
{
	ASSERT( getDim( ) == arg.getDim( ) );

	uint i;

	Vector tmp( arg );

	for( i=0; i<getDim( ); ++i )
		tmp.data[i] += data[i];

	return tmp;
}


inline Vector& Vector::operator+=(	const Vector& arg
									)
{
	ASSERT( getDim( ) == arg.getDim( ) );

	uint i;

	for( i=0; i<getDim( ); ++i )
		data[i] += arg.data[i];

	return *this;
}


inline Vector Vector::operator-(	const Vector& arg
									) const
{
	ASSERT( getDim( ) == arg.getDim( ) );

	uint i;

	Vector tmp(getDim());

	for( i=0; i<getDim( ); ++i )
		tmp.data[i] = data[i] - arg.data[i];

	return tmp;
}


inline Vector Vector::operator-=(	const Vector& arg
									)
{
	ASSERT( getDim( ) == arg.getDim( ) );

	uint i;

	for( i=0; i<getDim( ); ++i )
		data[i] -= arg.data[i];

	return *this;
}


inline Vector& Vector::operator*=( double scalar ){

    uint i;

    if ( fabs(scalar) >= ZERO_EPS )
        for( i=0; i<getDim( ); ++i )
            data[i] *= scalar;
    else  setZero( );

    return *this;
}


inline Vector& Vector::operator/=( double scalar ){

    uint i;

    if ( fabs(scalar) >= ZERO_EPS )
        for( i=0; i<getDim( ); ++i )
            data[i] /= scalar;

    return *this;
}


inline Vector Vector::operator*(	const Matrix& arg
									) const
{
	ASSERT( getDim( ) == arg.getNumRows( ) );

	uint i,j;
	Vector result( arg.getNumCols( ) );
	result.setZero( );

	for( i=0; i<arg.getNumCols( ); ++i )
		for( j=0; j<arg.getNumRows( ); ++j )
			result( i ) += operator()( j ) * arg( j,i );

	return result;
}


inline double Vector::operator^(	const Vector& arg
									) const
{
	ASSERT( getDim( ) == arg.getDim( ) );

	uint i;
	double result = 0.0;

	for( i=0; i<getDim( ); ++i )
		result += operator()( i ) * arg( i );

	return result;
}


inline Matrix Vector::operator%(	const Vector& arg
									) const
{
	uint i, j;
	Matrix result(getDim(), arg.getDim( ));

	for(i = 0; i < getDim(); ++i)
		for( j=0; j<arg.getDim( ); ++j )
			result( i,j ) = operator()( i ) * arg( j );

	return result;
}


inline returnValue Vector::setUnitVector(	uint idx
											)
{
	ASSERT( idx < getDim( ) );

	setZero( );
	operator()( idx ) = 1.0;

	return SUCCESSFUL_RETURN;
}


inline Vector Vector::absolute() {

    uint i;
    Vector result( getDim() );

    for( i = 0; i < getDim(); i++ )
        result.data[i] = fabs(data[i]);
    
    return result;
}

inline Vector Vector::getAbsolute() const {

    uint i;
    Vector result( getDim() );

    for( i = 0; i < getDim(); i++ )
        result.data[i] = fabs(data[i]);
    
    return result;
}




CLOSE_NAMESPACE_ACADO


/*
 *	end of file
 */
