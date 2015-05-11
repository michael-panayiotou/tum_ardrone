#include "sendCommand.h"
#include "EstimationNode.h"
#include <iostream>
#include <fstream>
#include <string>
#include <unistd.h>

sendCommand::sendCommand(EstimationNode* nde)
{

	node = nde;

}

void sendCommand::publish(){



	//node->publishCommand("c goto 0 0 0 10");
	node->publishCommand("c land");
		

}