class freqNode {
	public:
		int frequency;
		char symbol;		
		int huffCode; // change later, usually store bits not int (8bit not good);

        // children

        freqNode* left;
        freqNode* right;
};

class compareNode {
    public: 
        bool operator()(const freqNode &n1, const freqNode &n2) {
            if (n1.frequency == n2.frequency) {
                return true;
            }
            return n1.frequency > n2.frequency;
        }
};



