
#include <omp.h>

#include <cmath>
#include <algorithm>
#include <dipManager.h>



DipManager::DipManager()
{

}

DipManager::~DipManager()
{

}


// todo
void DipManager::dipExtract(void* _tau, void* _dip, void* _imgDip)
{
	if (!_dip || !_imgDip || !_tau ) return;
	double* tau = (double*)_tau;
	short* dip = (short*)_dip;
	double* imgDip = (double*)_imgDip;
	char* valid = (char*)m_imgValid;

	// omp_set_num_threads(5);
// #pragma omp parallel for
for (long add = 0; add < (long)m_size[1] * m_size[2]; add++)
	{
		// int tid = omp_get_thread_num();
		// fprintf(stderr, "--> %d\n", tid);
		double x = tau[add];
		int xi = (int)std::round(x);
		if (xi >= 0 && xi < m_size[0])
		{
			imgDip[add] = (double)dip[add * m_size[0] + xi] / (double)m_normShort;
			valid[add] = std::max(valid[add], (char)1);
		}
		else
		{
			imgDip[add] = 0.0;
			valid[add] = 0;
		}
	}
}


void DipManager::run(void* _tau)
{
	dipExtract(_tau, m_dipxy, m_imgDipxy);
	dipExtract(_tau, m_dipxz, m_imgDipxz);
}

