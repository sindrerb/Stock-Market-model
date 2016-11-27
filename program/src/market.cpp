#include "market.h"

Market::Market() {
    m_numberOfAgents = 0;
    m_marketCapital = 0;

}

void Market::initialzeMarket(int numberOfAgents, double agentInitalCapital) {
    m_numberOfAgents = numberOfAgents;
    m_marketCapital = numberOfAgents * agentInitalCapital;
    m_agents = new double[m_numberOfAgents + 1];
    m_agents[0] = 0;
    for ( int i = 1; i <= m_numberOfAgents; i++) {
        m_agents[i] = agentInitalCapital;
    }
}

//void Market::initialzeMarket(int numberOfAgents, double agentInitalCapital) {
//    m_numberOfAgents = numberOfAgents;
//    m_marketCapital = numberOfAgents * agentInitalCapital;
//    m_marketGrid = new double*[m_numberOfAgents];
//    for ( int i = 1; i <= m_numberOfAgents; i++) {
//        m_marketGrid[i] = new double[m_numberOfAgents];
//        for ( int j = 1; j <= m_numberOfAgents; j++) {
//            m_marketGrid[i][j] = agentInitalCapital;
//        }
//    }
//}

void Market::simulateTransactions(int numberOfTransactions, double smallesTransactionSize) {
    random_device rd;
    mt19937_64 gen{rd()};
    uniform_real_distribution<double> randomNumber(0.0,1.0);

    int possibleCapitalValues = m_marketCapital/smallesTransactionSize;
    m_transactionLog = new long int[possibleCapitalValues];

    for (int cycle = 0; cycle < numberOfTransactions; cycle++) {

        int i = (int) (randomNumber(gen)*(double)m_numberOfAgents + 1);
        int j = (int) (randomNumber(gen)*(double)m_numberOfAgents + 1);
        //        cout << i << j<< endl;
        if (i != j) {
            double transactionFactor = randomNumber(gen);
            double agentCapitalCombined = m_agents[i] + m_agents[j];
            double agent1_newCapital = transactionFactor * agentCapitalCombined;
            double agent2_newCapital = agentCapitalCombined - agent1_newCapital;
            if (agent1_newCapital > 0 && agent2_newCapital > 0) {
                m_agents[i] = agent1_newCapital;
                m_agents[j] = agent2_newCapital;

                int agent1_inLog = agent1_newCapital/smallesTransactionSize;
                int agent2_inLog = agent2_newCapital/smallesTransactionSize;
                m_transactionLog[agent1_inLog] += 1;
                m_transactionLog[agent2_inLog] += 1;
            }
        }
    }
}

void Market::writeLogToFile(string fileName) {
    string outputFile = fileName;
    outputFile.append(".txt");
    std::ofstream ofile;
    ofile.open(outputFile);//, std::ios_base::app);
    int arrayLength = m_marketCapital/0.01;
    for(int i = 1; i <= arrayLength ; i+=10) {
        ofile << m_transactionLog[i] << "\n" ;
    }
    ofile << std::endl;
    ofile.close();
}




/************************************/
/*        Setters & Getters         */
/************************************/
int Market::numberOfAgents() const {
    return m_numberOfAgents;
}

double Market::marketCapital() const {
    return m_marketCapital;
}

double *Market::agent() const {
    return m_agents;
}

long *Market::transactionLog() const {
    return m_transactionLog;
}

void Market::setNumberOfAgents(int numberOfAgents) {
    m_numberOfAgents = numberOfAgents;
}

void Market::setMarketCapital(double marketCapital) {
    m_marketCapital = marketCapital;
}

void Market::setAgents(double *agents) {
    m_agents = agents;
}

void Market::setTransactionLog(long *transactionLog) {
    m_transactionLog = transactionLog;
}


