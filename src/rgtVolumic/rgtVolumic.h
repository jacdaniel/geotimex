
#ifndef __RGTVOLUMIC__
#define __RGTVOLUMIC__

// class Solver;

class Constraint;
template <typename T> class LeakyIntegration;

class RgtVolumic
{
private:
	class Param
	{
	public:
		long size0 = 0;
		void* rhs = nullptr;
		// void* tau = nullptr;
		// Solver* solver = nullptr;
		LeakyIntegration<double>* leakyIntegration = nullptr;
	};
public:
	RgtVolumic();
	~RgtVolumic();
	void setSize(int* size) { for (int i = 0; i < 3; i++) m_size[i] = size[i]; }
	void setDipxy(void* data) { m_dipxy = data; }
	void setDipxz(void* data) { m_dipxz = data;  }
	void setNbIter(int iter) { m_nbIter = iter;  }
	void setEpsilon(double epsilon) { m_epsilon = epsilon;  }
	void setTau(void* tau) { m_tau = tau; }
	void setLeakyC(double val) { m_leakyC = val; }
	void setDipThreshold(double val) { m_dipThreshold = val;  }
	void setConstraint(Constraint *constraint) { m_constraint = constraint;  }
	void run();

	private:
		RgtVolumic::Param* m_param = nullptr;
		int m_size[3] = { 1,1,1 };
		void* m_dipxy = nullptr;
		void* m_dipxz = nullptr;
		int m_nbIter = 100;
		double m_epsilon = .1;
		void* m_tau = nullptr;
		double m_leakyC = 30.0;
		double m_dipThreshold = 2.0;
		bool paramInit();
		bool paramRelease();
		Constraint *m_constraint = nullptr;
};



#endif