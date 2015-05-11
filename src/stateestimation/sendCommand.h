



class EstimationNode;

class sendCommand 
{
private:
	EstimationNode* node;





public:
	sendCommand(EstimationNode* nde);
	~sendCommand();
	void publish();
	
};