/***********************************************************************************
 * Copyright (c) 2017, UT-Battelle
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *   * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 *   * Neither the name of the xacc nor the
 *     names of its contributors may be used to endorse or promote products
 *     derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL <COPYRIGHT HOLDER> BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * Contributors:
 *   Initial API and implementation - Alex McCaskey
 *
 **********************************************************************************/
#include "SymVerificationDecorator.hpp"
#include "VQERestartDecorator.hpp"
#include "PurificationDecorator.hpp"
#include "RDMPurificationDecorator.hpp"

#include "cppmicroservices/BundleActivator.h"
#include "cppmicroservices/BundleContext.h"
#include "cppmicroservices/ServiceProperties.h"

#include <memory>
#include <set>

using namespace cppmicroservices;

namespace {

/**
 */
class US_ABI_LOCAL DecoratorsActivator: public BundleActivator {

public:

	DecoratorsActivator() {
	}

	/**
	 */
	void Start(BundleContext context) {
		auto c = std::make_shared<xacc::vqe::SymVerificationDecorator>();
		auto c2 = std::make_shared<xacc::vqe::VQERestartDecorator>();
		auto c3 = std::make_shared<xacc::vqe::PurificationDecorator>();
		auto c4 = std::make_shared<xacc::vqe::RDMPurificationDecorator>();

		context.RegisterService<xacc::AcceleratorDecorator>(c);
        context.RegisterService<xacc::Accelerator>(c);

        context.RegisterService<xacc::AcceleratorDecorator>(c2);
        context.RegisterService<xacc::Accelerator>(c2);

        context.RegisterService<xacc::AcceleratorDecorator>(c3);
        context.RegisterService<xacc::Accelerator>(c3);

        context.RegisterService<xacc::AcceleratorDecorator>(c4);
        context.RegisterService<xacc::Accelerator>(c4);

	}

	/**
	 */
	void Stop(BundleContext /*context*/) {
	}

};

}

CPPMICROSERVICES_EXPORT_BUNDLE_ACTIVATOR(DecoratorsActivator)
