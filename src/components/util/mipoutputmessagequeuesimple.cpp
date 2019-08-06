/*
    
  This file is a part of EMIPLIB, the EDM Media over IP Library.
  
  Copyright (C) 2006-2016  Hasselt University - Expertise Centre for
                      Digital Media (EDM) (http://www.edm.uhasselt.be)

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  
  USA

*/

#include "mipconfig.h"
#include "mipoutputmessagequeuesimple.h"
#include "mipmessage.h"

#include "mipdebug.h"

MIPOutputMessageQueueSimple::MIPOutputMessageQueueSimple(const std::string &componentName) : MIPOutputMessageQueue(componentName)
{
}

MIPOutputMessageQueueSimple::~MIPOutputMessageQueueSimple()
{
}

bool MIPOutputMessageQueueSimple::push(const MIPComponentChain &chain, int64_t iteration, MIPMessage *pMsg)
{
	checkIteration(iteration);
	
	bool deleteMessage = true;
	bool gotError = false;

	MIPMessage *pNewMsg = pushSub(chain, iteration, pMsg, deleteMessage, gotError);
	if (gotError)
	{
		if (pNewMsg != 0 && deleteMessage) // clean up if necessary
			delete pNewMsg;

		return false;
	}

	if (pNewMsg != 0) // can be zero
		addToOutputQueue(pNewMsg, deleteMessage);

	return true;
}


