#include "./src/objectives.h"
#include "./src/objectiveD.h"
#include "./src/objectiveA_parte2.h"
#include "./src/objectiveB_parte2.h"
#include "./src/objectiveC_parte2.h"

int main(int argc, char *argv[]) {
    /*remove("../data/numberCores");
    remove("../data/numberLines");
    remove("../data/objectiveC_A");
    remove("../data/OperatingSystem");
    remove("../data/numberLines");
    remove("../data/outProducerConsumer.txt");
    remove("../data/outThreads.txt");
*/
    int saved_out = dup(1);
    objectiveB();
    dup2(saved_out, 1);
    objectiveC();
    dup2(saved_out, 1);
    socketServer();
    dup2(saved_out, 1);
    threads();
    dup2(saved_out, 1);
    threadsB();
    dup2(saved_out, 1);
    threadsC();
    dup2(saved_out, 1);

    return 0;
}
