#include "VectorCalculator.h"


VectorCalculator::VectorCalculator(){}

std::vector<double> VectorCalculator::set( double x, double y, double z)
{
    std::vector<double> v ;
    v.resize(3) ;
    v[0] = x ;
    v[1] = y ;
    v[2] = z ;
    return v ;
}

std::vector<double> VectorCalculator::initialize( std::vector<double> A, double B )
{
    A.resize(3) ;
    for( int i = 0 ; i < A.size() ; i++ )
        A[i] = B ;
    return A ;
}

std::vector<double> VectorCalculator::add( std::vector<double> A, std::vector<double> B )
{
    std::vector<double> C ;
    for ( int i = 0 ; i < A.size() ; i++ )
        C.push_back(A[i] + B[i]) ;
    return C ;
}

double VectorCalculator::dot( std::vector<double> A, std::vector<double> B )
{
    double dot = 0.0 ;
    for ( int i = 0 ; i < A.size() ; i++ )
        dot = dot + (A[i]*B[i]) ;
    return dot ;
}

std::vector<double> VectorCalculator::cross( std::vector<double> A, std::vector<double> B )
{
    std::vector<double> C ;
    C.push_back( (A[1]*B[2]) - (A[2]*B[1]) ) ;
    C.push_back( (int)(A[2]*B[0]) - (A[0]*B[2]) ) ;
    C.push_back( (A[0]*B[1]) - (A[1]*B[0]) ) ;
    
    return C ;
}

std::vector<double> VectorCalculator::multiply( std::vector<double> A, double B )
{
    for ( int i = 0 ; i < A.size() ; i++ )
        A[i] = A[i] * B ;
    return A ;
}

std::vector<double> VectorCalculator::subtract( std::vector<double> A, std::vector<double> B )
{
    std::vector<double> C ;
    for ( int i = 0 ; i < A.size() ; i++ )
        C.push_back(A[i] - B[i]) ;
    return C ;
}

double VectorCalculator::magnitude( std::vector<double> A )
{
    double sum = 0.0 ;
    for ( int i = 0 ; i < A.size() ; i++ )
        sum = sum + (A[i]*A[i]) ;
    return sqrt(sum) ;
}

std::vector<double> VectorCalculator::normalize( std::vector<double> A )
{
    double tmp = magnitude(A) ;
    for ( int i = 0 ; i < A.size() ; i++ )
        A[i] = A[i] / tmp ;
    return A ;
}

std::vector<double> VectorCalculator::hadamard_product( std::vector<double> A, std::vector<double> B )
{
    std::vector<double> C ;
    for ( int i = 0 ; i < A.size() ; i++ )
        C.push_back(A[i] * B[i]) ;
    return C ;
}

std::vector<double> VectorCalculator::clamp( std::vector<double> A )
{
    for( int i = 0 ; i < A.size() ; i++ ){
        if( A[i] > 1 )
            A[i] = 1.0 ;
        else if( A[i] < 0 )
            A[i] = 0.0 ;
    }
    return A ;
}

double VectorCalculator::clamp_value( double a )
{
    if( a < 0 )
        a = 0.0 ;
    if( a > 1 )
        a = 1.0 ;
    return a ;
}

std::vector<double> VectorCalculator::add_scalar( std::vector<double> A, double scalar )
{
    for( int i = 0 ; i < A.size() ; i++ )
        A[i] = A[i] + scalar ;
    return A ;
}

double VectorCalculator::generate_random_number( double min, double max )
{
    std::random_device rd ;
    std::default_random_engine eng(rd());
    std::uniform_real_distribution<double> distr( min, max ) ;
    return distr(eng) ;
    
}

std::vector<double> VectorCalculator::Multiply( std::vector<std::vector<double>> matrix, std::vector<double> vec )
{
    std::vector<double> result(vec.size(), 0.0);
    for (int i = 0; i < matrix.size(); ++i) {
        for (int j = 0; j < vec.size(); ++j) {
            result[i] += matrix[i][j] * vec[j];
        }
    }

    return result;
}

std::vector<double> VectorCalculator::power( std::vector<double> A, double p )
{
    A[0] = pow(A[0],p) ;
    A[1] = pow(A[1],p) ;
    A[2] = pow(A[2],p) ;
    return A ; 
}

VectorCalculator::~VectorCalculator(){}
