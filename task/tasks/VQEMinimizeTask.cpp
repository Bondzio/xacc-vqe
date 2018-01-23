#include "VQEMinimizeTask.hpp"

#include "VQEProgram.hpp"


namespace xacc {
namespace vqe {

double VQEMinimizeTask::value(const Eigen::VectorXd& params) {
	auto r = computeTask->execute(params);
	currentEnergy = r.results[0].second;
	return currentEnergy;
}

VQETaskResult VQEMinimizeTask::execute(
		Eigen::VectorXd parameters) {
	currentEnergy = 0.0;
	computeTask = std::make_shared<ComputeEnergyVQETask>(program);
	cppoptlib::NelderMeadSolver<VQEMinimizeTask> solver;
	solver.setStopCriteria(VQEMinimizeTask::getConvergenceCriteria());
	solver.minimize(*this, parameters);

	std::stringstream ss;
	ss << computeTask->totalQpuCalls << " total QPU calls over " << computeTask->vqeIteration << " VQE iterations.";
	xacc::info("");
	xacc::info(ss.str());

	VQETaskResult r;
	r.angles = parameters;
	r.energy = currentEnergy;
	r.vqeIterations = computeTask->vqeIteration;
	r.nQpuCalls = computeTask->totalQpuCalls;
//	r.results.push_back({parameters, currentEnergy});
	return r;
}

}
}
