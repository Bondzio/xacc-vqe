#include "FermionToSpinTransformation.hpp"
#include <iostream>
#include <unordered_map>

#include "DiagonalizeTask.hpp"

namespace xacc {
namespace vqe {


VQETaskResult DiagonalizeTask::execute(
		Eigen::VectorXd parameters) {
	int nQubits = std::stoi(xacc::getOption("n-qubits"));

	boost::mpi::communicator world;

	auto hamiltonianInstruction = program->getPauliOperator();

	std::shared_ptr<DiagonalizeBackend> backend;
	if (xacc::optionExists("diagonalize-backend")) {
		auto str = xacc::getOption("diagonalize-backend");
		backend = ServiceRegistry::instance()->getService<
				DiagonalizeBackend>(str);
	} else {
		backend = ServiceRegistry::instance()->getService<
				DiagonalizeBackend>("diagonalize-eigen");
	}

	auto energy = backend->diagonalize(hamiltonianInstruction,
			nQubits);
	return std::vector<std::pair<Eigen::VectorXd, double>> { { parameters,
			energy } };
}

double EigenDiagonalizeBackend::diagonalize(
		PauliOperator& inst, const int nQubits) {
	boost::mpi::communicator world;
//	= inst.toSparseRealMatrix(
//			nQubits);

//	auto nTerms = inst.nInstructions();
//
//	// Get Identity coefficient
//	std::complex<double> identityCoeff(0.0, 0.0);
//	for (int i = 0; i < nTerms; i++) {
//		std::shared_ptr<SpinInstruction> spinInst = std::dynamic_pointer_cast<
//				SpinInstruction>(inst.getInstruction(i));
//		if (spinInst->isIdentity()) {
//			identityCoeff = spinInst->coefficient;
//			break;
//		}
//	}
//
//	std::size_t dim = 1;
//	std::size_t two = 2;
//	for (int i = 0; i < nQubits; i++)
//		dim *= two;
//
//	// Generate all bit strings
//	std::vector<std::string> bitStrings(dim);
//#pragma omp parallel for
//	for (std::uint64_t j = 0; j < dim; j++) {
//
//		std::stringstream s;
//		for (int k = nQubits - 1; k >= 0; k--) {
//			s << ((j >> k) & 1);
//		}
//		bitStrings[j] = s.str();
//	}
//
//	int Istart =0;
//	int Iend = dim;
//
//	using Triplet = Eigen::Triplet<double>;
//	using IndexPair = std::pair<std::uint64_t, std::uint64_t>;
//
//	std::unordered_map<IndexPair,
//					std::complex<double>,
//					boost::hash<IndexPair> > nonZeros;
//
//	for (int i = 0; i < dim; i++)
//			nonZeros.insert(
//					std::make_pair(IndexPair { i, i },
//							std::complex<double>(0, 0)));
//
//	std::vector<Triplet> triplets;
//	for (std::uint64_t myRow = Istart; myRow < Iend; myRow++) {
//
//		XACCInfo(
//				"Matrix Construction for rank " + std::to_string(0)
//						+ ", row " + std::to_string(myRow));
//
//		if (identityCoeff != std::complex<double>(0.0, 0.0)) {
//			nonZeros[std::make_pair(myRow,myRow)] += identityCoeff;
//		}
//
//		for (int i = 0; i < nTerms; i++) {
//
//			std::shared_ptr<SpinInstruction> spinInst =
//					std::dynamic_pointer_cast<SpinInstruction>(
//							inst.getInstruction(i));
//			std::pair<std::string, std::complex<double>> newBitStrCoeff;
//
//			if (!spinInst->isIdentity()) {
//				if (spinInst->isDiagonal()) {
//					newBitStrCoeff = spinInst->computeActionOnBra(
//							bitStrings[myRow]);
//					nonZeros[std::make_pair(myRow,myRow)] += newBitStrCoeff.second;
//				} else {
//					newBitStrCoeff = spinInst->computeActionOnBra(
//							bitStrings[myRow]);
//					std::uint64_t k = std::stol(newBitStrCoeff.first, nullptr,
//							2);
//
//					auto p = std::make_pair(myRow, k);
//					if (nonZeros.find(p) != nonZeros.end()) {
//						nonZeros[p] += newBitStrCoeff.second;
//					} else {
//						nonZeros.insert(
//								std::make_pair(p, newBitStrCoeff.second));
//					}
//				}
//			}
//		}
//	}
//
//	for (auto& kv : nonZeros) {
//		triplets.push_back(Triplet(kv.first.first, kv.first.second, std::real(kv.second)));
//	}
//
//	Eigen::SparseMatrix<double> ham(dim,dim);
//	ham.setFromTriplets(triplets.begin(), triplets.end());
//	ham.makeCompressed();
//
//	Eigen::SelfAdjointEigenSolver<Eigen::SparseMatrix<double>> es(
//			ham);
//	auto eigenvalues = es.eigenvalues();
//	std::stringstream ss;
//	ss << eigenvalues.transpose();
//	if (world.rank() == 0)
//		XACCInfo("HamiltonianEigenvalues:\n" + ss.str());
//	return std::real(eigenvalues(0));
	return 0.0;
}

}
}
