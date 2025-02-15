#ifndef _STAT_DISTRIBUTIONS_
#define _STAT_DISTRIBUTIONS_

#include "well512.h"

//##################################################################################
class Distribution
{
	std::string m_type;
	double m_alpha;
	double m_beta;
public:
	Distribution();
	Distribution(double alpha, double beta, std::string type);
	virtual bool IsBinary();
	virtual double GetVariate(WELLFiveTwelve &gen);
	std::string GetType();
	double GetAlpha();
	double GetBeta();
	~Distribution();
};

//##################################################################################
/*
This is an object that performs inverse CDF's of the exponential distribution.
*/
class ExponentialDist : public Distribution
{
public:
	ExponentialDist();
	ExponentialDist(double alpha, double beta, std::string type);
	bool IsBinary() override;
	double GetVariate(WELLFiveTwelve &gen) override;
	//using Distribution::GetType;
};
//##################################################################################
/*
This is an object that performs inverse CDF's of the gamma
distribution, using an algorithm found in Fishman's book 'Monte Carlo...'.
*/
class GammaDist : public Distribution
{
public:
	GammaDist();
	GammaDist(double alpha, double beta, std::string type) :
		Distribution::Distribution(alpha, beta, type) {}
	bool IsBinary() override;
	double GetVariate(WELLFiveTwelve &gen) override;
	//using Distribution::GetType;
};

//##################################################################################
/*
This is an object that performs inverse CDF's of the bounded Johnson
distribution, using an algorithm for the normal inverse CDF and translation for
the normal.
*/

class BoundedJohnsonDist  : public Distribution
{
	double m_gamma;
	double m_delta;
	double m_xi;
	double m_lambda;
public:
	BoundedJohnsonDist ();
	BoundedJohnsonDist (
		double gamma, double delta, double xi, double lambda, std::string type
	);
	bool IsBinary() override;
	double RationalApproximation(double u);
	double NormalCDFInverse(double p);
	double GetInverseCDF(double u);
	double GetVariate(WELLFiveTwelve &gen) override;
	//using Distribution::GetType;
};


//##################################################################################
/*
this is an object that performs inverse CDF's of the beta
distribution using an algorithm found in Fishman's book 'Monte Carlo...'.
*/
class BetaDist : public Distribution
{
	GammaDist m_alpha_dist;
	GammaDist m_beta_dist;
public:
	BetaDist();
	BetaDist(double alpha, double beta, std::string type);
	bool IsBinary() override;
	double GetVariate(WELLFiveTwelve &gen) override;
	//using Distribution::GetType;
};


class GammaProcessDist
{
	double m_b;
	double m_c;
	double m_beta;
	std::string m_type;
public:
	GammaProcessDist();
	GammaProcessDist(double b, double c, double beta, std::string type);
	bool IsBinary();
	double GetAlpha(double t, double delta_t);
	double GetVariate(double alpha, WELLFiveTwelve &gen);
	std::string GetType();
	double GetBeta();
	double GetMean(double t, double delta_t);
};


class InvGammaDist : public GammaDist
{
public:
	InvGammaDist();
	InvGammaDist(double alpha, double beta, std::string type) :
		GammaDist::GammaDist(alpha, beta, type) {}
	double GetVariate(WELLFiveTwelve &gen) override;
};

#endif
