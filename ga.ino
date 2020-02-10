// random number generator codes are mostly different, for more randomness

// create new random population for all 5 islands
void createPopulation()
{
    // generate island1
    for (int i = 0; i < island1Size; i++)
    {
        island1[i].wLines       = (((double) esp_random() / UINT32_MAX) - 0.5) * 2.0;
        island1[i].wDeltaHeight = (((double) esp_random() / UINT32_MAX) - 0.5) * 2.0;
        island1[i].wHoles       = (((double) esp_random() / UINT32_MAX) - 0.5) * 2.0;
        island1[i].wBigWells    = (((double) esp_random() / UINT32_MAX) - 0.5) * 2.0;
        island1[i].wMaxHoleDist = (((double) esp_random() / UINT32_MAX) - 0.5) * 2.0;
        island1[i].wBumpiness   = (((double) esp_random() / UINT32_MAX) - 0.5) * 2.0;

        island1[i].score        = 0; // debug with esp_random() % MAXSCORE-1
        island1[i].lines        = 0;

        island1[i].originGeneration = generation;
        island1[i].originIsland     = ISLAND1_ID;

        //Serial.println(island1[i].toString());
    }

    // generate island2
    for (int i = 0; i < island2Size; i++)
    {
        island2[i].wLines       = (((double) esp_random() / UINT32_MAX) - 0.5) * 2.0;
        island2[i].wDeltaHeight = (((double) esp_random() / UINT32_MAX) - 0.5) * 2.0;
        island2[i].wHoles       = (((double) esp_random() / UINT32_MAX) - 0.5) * 2.0;
        island2[i].wBigWells    = (((double) esp_random() / UINT32_MAX) - 0.5) * 2.0;
        island2[i].wMaxHoleDist = (((double) esp_random() / UINT32_MAX) - 0.5) * 2.0;
        island2[i].wBumpiness   = (((double) esp_random() / UINT32_MAX) - 0.5) * 2.0;

        island2[i].score        = 0;
        island2[i].lines        = 0;

        island2[i].originGeneration = generation;
        island2[i].originIsland     = ISLAND2_ID;

        //Serial.println(island2[i].toString());
    }

    // generate island3
    for (int i = 0; i < island3Size; i++)
    {
        island3[i].wLines       = (((double) esp_random() / UINT32_MAX) - 0.5) * 2.0;
        island3[i].wDeltaHeight = (((double) esp_random() / UINT32_MAX) - 0.5) * 2.0;
        island3[i].wHoles       = (((double) esp_random() / UINT32_MAX) - 0.5) * 2.0;
        island3[i].wBigWells    = (((double) esp_random() / UINT32_MAX) - 0.5) * 2.0;
        island3[i].wMaxHoleDist = (((double) esp_random() / UINT32_MAX) - 0.5) * 2.0;
        island3[i].wBumpiness   = (((double) esp_random() / UINT32_MAX) - 0.5) * 2.0;

        island3[i].score        = 0;
        island3[i].lines        = 0;

        island3[i].originGeneration = generation;
        island3[i].originIsland     = ISLAND3_ID;

        //Serial.println(island3[i].toString());
    }

    // generate island4
    for (int i = 0; i < island4Size; i++)
    {
        island4[i].wLines       = (((double) esp_random() / UINT32_MAX) - 0.5) * 2.0;
        island4[i].wDeltaHeight = (((double) esp_random() / UINT32_MAX) - 0.5) * 2.0;
        island4[i].wHoles       = (((double) esp_random() / UINT32_MAX) - 0.5) * 2.0;
        island4[i].wBigWells    = (((double) esp_random() / UINT32_MAX) - 0.5) * 2.0;
        island4[i].wMaxHoleDist = (((double) esp_random() / UINT32_MAX) - 0.5) * 2.0;
        island4[i].wBumpiness   = (((double) esp_random() / UINT32_MAX) - 0.5) * 2.0;

        island4[i].score        = 0;
        island4[i].lines        = 0;

        island4[i].originGeneration = generation;
        island4[i].originIsland     = ISLAND4_ID;

        //Serial.println(island4[i].toString());
    }

    // generate elite island
    for (int i = 0; i < islandEliteSize; i++)
    {
        islandElite[i].wLines       = (((double) esp_random() / UINT32_MAX) - 0.5) * 2.0;
        islandElite[i].wDeltaHeight = (((double) esp_random() / UINT32_MAX) - 0.5) * 2.0;
        islandElite[i].wHoles       = (((double) esp_random() / UINT32_MAX) - 0.5) * 2.0;
        islandElite[i].wBigWells    = (((double) esp_random() / UINT32_MAX) - 0.5) * 2.0;
        islandElite[i].wMaxHoleDist = (((double) esp_random() / UINT32_MAX) - 0.5) * 2.0;
        islandElite[i].wBumpiness   = (((double) esp_random() / UINT32_MAX) - 0.5) * 2.0;

        islandElite[i].score        = 0;
        islandElite[i].lines        = 0;

        islandElite[i].originGeneration = generation;
        islandElite[i].originIsland     = ISLANDELITE_ID;

        //Serial.println(islandElite[i].toString());
    }

}


// initialize the genetic algorithm
void initializeGA()
{
    currentChromosomeID = 0;
    currentIslandID     = ISLAND1_ID;
    generation          = 0;

    createPopulation();

    // set values for AI
    wLines         = island1[currentChromosomeID].wLines;
    wDeltaHeight   = island1[currentChromosomeID].wDeltaHeight;
    wHoles         = island1[currentChromosomeID].wHoles;
    wBigWells      = island1[currentChromosomeID].wBigWells;
    wMaxHoleDist   = island1[currentChromosomeID].wMaxHoleDist;
    wBumpiness     = island1[currentChromosomeID].wBumpiness;
}


void updateGA()
{
    switch (currentIslandID)
    {
        case ISLAND1_ID:
        {
            // set results
            island1[currentChromosomeID].score = score;
            island1[currentChromosomeID].lines = lines;

            // move on to next chromosome
            currentChromosomeID++;
            if (currentChromosomeID == island1Size)
            {
                // move on to island2 
                currentIslandID = ISLAND2_ID;
                currentChromosomeID = 0;

                wLines         = island2[currentChromosomeID].wLines;
                wDeltaHeight   = island2[currentChromosomeID].wDeltaHeight;
                wHoles         = island2[currentChromosomeID].wHoles;
                wBigWells      = island2[currentChromosomeID].wBigWells;
                wMaxHoleDist   = island2[currentChromosomeID].wMaxHoleDist;
                wBumpiness     = island2[currentChromosomeID].wBumpiness;
            }
            else
            {
                wLines         = island1[currentChromosomeID].wLines;
                wDeltaHeight   = island1[currentChromosomeID].wDeltaHeight;
                wHoles         = island1[currentChromosomeID].wHoles;
                wBigWells      = island1[currentChromosomeID].wBigWells;
                wMaxHoleDist   = island1[currentChromosomeID].wMaxHoleDist;
                wBumpiness     = island1[currentChromosomeID].wBumpiness;
            }
            break;
        }

        case ISLAND2_ID:
        {
            // set results
            island2[currentChromosomeID].score = score;
            island2[currentChromosomeID].lines = lines;

            // move on to next chromosome
            currentChromosomeID++;
            if (currentChromosomeID == island2Size)
            {
                // move on to island3 
                currentIslandID = ISLAND3_ID;
                currentChromosomeID = 0;

                wLines         = island3[currentChromosomeID].wLines;
                wDeltaHeight   = island3[currentChromosomeID].wDeltaHeight;
                wHoles         = island3[currentChromosomeID].wHoles;
                wBigWells      = island3[currentChromosomeID].wBigWells;
                wMaxHoleDist   = island3[currentChromosomeID].wMaxHoleDist;
                wBumpiness     = island3[currentChromosomeID].wBumpiness;
            }
            else
            {
                wLines         = island2[currentChromosomeID].wLines;
                wDeltaHeight   = island2[currentChromosomeID].wDeltaHeight;
                wHoles         = island2[currentChromosomeID].wHoles;
                wBigWells      = island2[currentChromosomeID].wBigWells;
                wMaxHoleDist   = island2[currentChromosomeID].wMaxHoleDist;
                wBumpiness     = island2[currentChromosomeID].wBumpiness;
            }
            break;
        }

        case ISLAND3_ID:
        {
            // set results
            island3[currentChromosomeID].score = score;
            island3[currentChromosomeID].lines = lines;

            // move on to next chromosome
            currentChromosomeID++;
            if (currentChromosomeID == island3Size)
            {
                // move on to island4 
                currentIslandID = ISLAND4_ID;
                currentChromosomeID = 0;

                wLines         = island4[currentChromosomeID].wLines;
                wDeltaHeight   = island4[currentChromosomeID].wDeltaHeight;
                wHoles         = island4[currentChromosomeID].wHoles;
                wBigWells      = island4[currentChromosomeID].wBigWells;
                wMaxHoleDist   = island4[currentChromosomeID].wMaxHoleDist;
                wBumpiness     = island4[currentChromosomeID].wBumpiness;
            }
            else
            {
                wLines         = island3[currentChromosomeID].wLines;
                wDeltaHeight   = island3[currentChromosomeID].wDeltaHeight;
                wHoles         = island3[currentChromosomeID].wHoles;
                wBigWells      = island3[currentChromosomeID].wBigWells;
                wMaxHoleDist   = island3[currentChromosomeID].wMaxHoleDist;
                wBumpiness     = island3[currentChromosomeID].wBumpiness;
            }
            break;
        }

        case ISLAND4_ID:
        {
            // set results
            island4[currentChromosomeID].score = score;
            island4[currentChromosomeID].lines = lines;

            // move on to next chromosome
            currentChromosomeID++;
            if (currentChromosomeID == island4Size)
            {
                // move on to elite island
                currentIslandID = ISLANDELITE_ID;
                currentChromosomeID = 0;

                wLines         = islandElite[currentChromosomeID].wLines;
                wDeltaHeight   = islandElite[currentChromosomeID].wDeltaHeight;
                wHoles         = islandElite[currentChromosomeID].wHoles;
                wBigWells      = islandElite[currentChromosomeID].wBigWells;
                wMaxHoleDist   = islandElite[currentChromosomeID].wMaxHoleDist;
                wBumpiness     = islandElite[currentChromosomeID].wBumpiness;
            }
            else
            {
                wLines         = island4[currentChromosomeID].wLines;
                wDeltaHeight   = island4[currentChromosomeID].wDeltaHeight;
                wHoles         = island4[currentChromosomeID].wHoles;
                wBigWells      = island4[currentChromosomeID].wBigWells;
                wMaxHoleDist   = island4[currentChromosomeID].wMaxHoleDist;
                wBumpiness     = island4[currentChromosomeID].wBumpiness;
            }
            break;
        }

        case ISLANDELITE_ID:
        {
            // set results
            islandElite[currentChromosomeID].score = score;
            islandElite[currentChromosomeID].lines = lines;

            // move on to next chromosome
            currentChromosomeID++;
            if (currentChromosomeID == islandEliteSize)
            {
                // reset IDs
                currentIslandID = ISLAND1_ID;
                currentChromosomeID = 0;

                // end generation and go to the next one
                updateGeneraion();

                // setup variables for AI
                currentChromosomeID = 0;
                currentIslandID     = ISLAND1_ID;

                wLines         = island1[currentChromosomeID].wLines;
                wDeltaHeight   = island1[currentChromosomeID].wDeltaHeight;
                wHoles         = island1[currentChromosomeID].wHoles;
                wBigWells      = island1[currentChromosomeID].wBigWells;
                wMaxHoleDist   = island1[currentChromosomeID].wMaxHoleDist;
                wBumpiness     = island1[currentChromosomeID].wBumpiness;
            }
            else
            {
                wLines         = islandElite[currentChromosomeID].wLines;
                wDeltaHeight   = islandElite[currentChromosomeID].wDeltaHeight;
                wHoles         = islandElite[currentChromosomeID].wHoles;
                wBigWells      = islandElite[currentChromosomeID].wBigWells;
                wMaxHoleDist   = islandElite[currentChromosomeID].wMaxHoleDist;
                wBumpiness     = islandElite[currentChromosomeID].wBumpiness;
            }
            break;
        }
    }

}


// randomly shuffles given array of indexes
void randomShuffleIndexes(int indexes[], int arraySize)
{
    for (int i=0; i < arraySize; i++) {
       int n = random(0, arraySize);
       int temp = indexes[n];
       indexes[n] =  indexes[i];
       indexes[i] = temp;
    }
}


// generates crossover from two given parents (indices) on a given island, with mutation probability
chromosome crossOver(chromosome island[], int parent2, int parent1)
{
    chromosome child;

    child.score        = 0;
    child.lines        = 0;

    child.originGeneration = generation + 1;
    child.originIsland     = currentIslandID; // ID should be set correctly during update island function

    if (esp_random() % 101 <= MUTATION_PROB_CHILD*100){
        childMutationsInCurrentGen++;
        child.wLines = (((double) esp_random() / UINT32_MAX) - 0.5) * 2.0; // mutate
    } else {
        if (esp_random() % 2 == 1) 
            child.wLines = island[parent1].wLines;
        else child.wLines = island[parent2].wLines;
    }

    if (esp_random() % 101 <= MUTATION_PROB_CHILD*100){
        childMutationsInCurrentGen++;
        child.wDeltaHeight = (((double) esp_random() / UINT32_MAX) - 0.5) * 2.0; // mutate
    } else {
        if (esp_random() % 2 == 1) 
            child.wDeltaHeight = island[parent1].wDeltaHeight;
        else child.wDeltaHeight = island[parent2].wDeltaHeight;
    }

    if (esp_random() % 101 <= MUTATION_PROB_CHILD*100){
        childMutationsInCurrentGen++;
        child.wHoles = (((double) esp_random() / UINT32_MAX) - 0.5) * 2.0; // mutate
    } else {
        if (esp_random() % 2 == 1) 
            child.wHoles = island[parent1].wHoles;
        else child.wHoles = island[parent2].wHoles;
    }

    if (esp_random() % 101 <= MUTATION_PROB_CHILD*100){
        childMutationsInCurrentGen++;
        child.wBigWells = (((double) esp_random() / UINT32_MAX) - 0.5) * 2.0; // mutate
    } else {
        if (esp_random() % 2 == 1) 
            child.wBigWells = island[parent1].wBigWells;
        else child.wBigWells = island[parent2].wBigWells;
    }

    if (esp_random() % 101 <= MUTATION_PROB_CHILD*100){
        childMutationsInCurrentGen++;
        child.wMaxHoleDist = (((double) esp_random() / UINT32_MAX) - 0.5) * 2.0; // mutate
    } else {
        if (esp_random() % 2 == 1) 
            child.wMaxHoleDist = island[parent1].wMaxHoleDist;
        else child.wMaxHoleDist = island[parent2].wMaxHoleDist;
    }

    if (esp_random() % 101 <= MUTATION_PROB_CHILD*100){
        childMutationsInCurrentGen++;
        child.wBumpiness = (((double) esp_random() / UINT32_MAX) - 0.5) * 2.0; // mutate
    } else {
        if (esp_random() % 2 == 1) 
            child.wBumpiness = island[parent1].wBumpiness;
        else child.wBumpiness = island[parent2].wBumpiness;
    }

    return child;
}


// returns fittest of two candidates (indexes) of a given island 
int getFittest(chromosome island[], int candidate1, int candidate2)
{
    // for same score, give advantage to candidate1
    if (island[candidate1].score >= island[candidate2].score)
        return candidate1;
    else
        return candidate2;
}


// returns true if given value is present in given array with given size
bool isInArray(int array[], int size, int value)
{
    bool found = false;
    for (int i = 0; i < size; i++) {
        if (array[i] == value) found = true;
    }
    return found;
}


// writes the islandSize/4 weakes indices of the given island in weakest[]
void getWeakest(chromosome island[], int islandSize, int weakest[])
{
    // initialize weakest[] with negative values to prevent issues with isInArray()
    for (int i = 0; i < islandSize/4; i++)
        weakest[i] = -1;

    // select the islandSize/4 weakest
    for (int selectedCounter = 0; selectedCounter < islandSize/4; selectedCounter++)
    {
        int lowestScore = INT32_MAX;    // since 0 is the lowest score
        int lowestScoreIndex = 0;       // keep track of index of lowest score
        for (int i = 0; i < islandSize; i++)
        {
            // make sure we do not have already selected this index
            if (island[i].score < lowestScore && !isInArray(weakest, islandSize/4, i))
            {
                lowestScoreIndex = i;
                lowestScore = island[i].score;
            }
        }
        // add weakest to weakest list
        weakest[selectedCounter] = lowestScoreIndex;
    }   
}


// performs random mutations on entire given island
void mutateIsland(chromosome island[], int islandSize)
{
    for (int i = 0; i < islandSize; i++)
    {
        if (esp_random() % 101 <= MUTATION_PROB_ANY*100){
        generalMutationsInCurrentGen++;
        island[i].wLines = (((double) esp_random() / UINT32_MAX) - 0.5) * 2.0; // mutate
        }
        
        if (esp_random() % 101 <= MUTATION_PROB_ANY*100){
        generalMutationsInCurrentGen++;
        island[i].wDeltaHeight = (((double) esp_random() / UINT32_MAX) - 0.5) * 2.0; // mutate
        }
        
        if (esp_random() % 101 <= MUTATION_PROB_ANY*100){
        generalMutationsInCurrentGen++;
        island[i].wHoles = (((double) esp_random() / UINT32_MAX) - 0.5) * 2.0; // mutate
        }
        
        if (esp_random() % 101 <= MUTATION_PROB_ANY*100){
        generalMutationsInCurrentGen++;
        island[i].wBigWells = (((double) esp_random() / UINT32_MAX) - 0.5) * 2.0; // mutate
        }
        
        if (esp_random() % 101 <= MUTATION_PROB_ANY*100){
        generalMutationsInCurrentGen++;
        island[i].wMaxHoleDist = (((double) esp_random() / UINT32_MAX) - 0.5) * 2.0; // mutate
        }
        
        if (esp_random() % 101 <= MUTATION_PROB_ANY*100){
        generalMutationsInCurrentGen++;
        island[i].wBumpiness = (((double) esp_random() / UINT32_MAX) - 0.5) * 2.0; // mutate
        }
    }
}


// updates given island
void updateIsland(chromosome island[], int islandSize)
{
    // print island population
    /*
    for (int i = 0; i < islandSize; i++)
    {
        Serial.print(i);
        Serial.print(": ");
        Serial.println(island[i].toString());
    }
    Serial.println();
    */


    // create random indexes used for creating pairs
    int pairIndexes[islandSize];
    for (int i = 0; i < islandSize; i++)
    {
        pairIndexes[i] = i;
    }
    randomShuffleIndexes(pairIndexes, islandSize);
    

    // for each pair, select the fittest by tournament selection (of size 2)
    int winners[islandSize/2];
    for (int i = 0; i < (islandSize/2); i++)
    {
        /*
        Serial.print(pairIndexes[i*2]);
        Serial.print(" ");
        Serial.print(pairIndexes[i*2 + 1]);
        Serial.print(" winner: ");
        Serial.println(getFittest(island, pairIndexes[i*2], pairIndexes[i*2 + 1]));
        */
        winners[i] = getFittest(island, pairIndexes[i*2], pairIndexes[i*2 + 1]);
    }

    // the winners (parents) are already randomized, so no need for that anymore

    // create offspring
    chromosome offspring[islandSize/4];
    for (int i = 0; i < (islandSize/4); i++)
    {
        offspring[i] = crossOver(island, winners[i*2], winners[i*2 + 1]);
        /*
        Serial.print(winners[i*2]);
        Serial.print(" ");
        Serial.print(winners[i*2 + 1]);
        Serial.print(" child: ");
        Serial.println(offspring[i].toString());
        */
    }

    // find the islandSize/4 weakest to replace them
    int weakest[islandSize/4];
    getWeakest(island, islandSize, weakest);

    /*
    for (int i = 0; i < (islandSize/4); i++)
    {
        Serial.print(weakest[i]);
        Serial.print(": ");
        Serial.println(island[weakest[i]].toString());
    }
    */

    // replace the weakest
    for (int i = 0; i < (islandSize/4); i++)
    {
        island[weakest[i]] = offspring[i];
    }


    // do random mutations on entire island population
    mutateIsland(island, islandSize);

    // print new island population
    /*
    Serial.println("New population:");
    for (int i = 0; i < islandSize; i++)
    {
        Serial.print(i);
        Serial.print(": ");
        Serial.println(island[i].toString());
    }
    Serial.println();
    */

}


// returns best performing chromosome index of a given island
int getBestPerformerOfIsland(chromosome island[], int islandSize)
{
    int bestScore = 0;
    int bestScoringIndex = 0;

    for (int i = 0; i < islandSize; i++)
    {
        if (island[i].score > bestScore)
        {
            bestScore = island[i].score;
            bestScoringIndex = i;
        }
    }
    return bestScoringIndex;
}

// migrates each best performer of the previous generation to the elite island
// in return for a random chromosome
void doMigration()
{
    // create random indexes to select chromosomes that will be sent away from the elite island
    int randomIndexes[islandEliteSize];
    for (int i = 0; i < islandEliteSize; i++)
    {
        randomIndexes[i] = i;
    }
    randomShuffleIndexes(randomIndexes, islandEliteSize);

    // use the first four indexes of the random indexes to select the migrator
    // put them in virtual boats
    chromosome migratorToIsland1 = islandElite[randomIndexes[0]];
    chromosome migratorToIsland2 = islandElite[randomIndexes[1]];
    chromosome migratorToIsland3 = islandElite[randomIndexes[2]];
    chromosome migratorToIsland4 = islandElite[randomIndexes[3]];

    /*
    Serial.println("randos from elite island to be sent away:");
    Serial.print(randomIndexes[0]); Serial.print(": ");
    Serial.println(migratorToIsland1.toString());
    Serial.print(randomIndexes[1]); Serial.print(": ");
    Serial.println(migratorToIsland2.toString());
    Serial.print(randomIndexes[2]); Serial.print(": ");
    Serial.println(migratorToIsland3.toString());
    Serial.print(randomIndexes[3]); Serial.print(": ");
    Serial.println(migratorToIsland4.toString());
    Serial.println();
    */

    // for each of the other four islands, select the best performer
    int bestIsland1PerformerIndex = getBestPerformerOfIsland(island1, island1Size);
    int bestIsland2PerformerIndex = getBestPerformerOfIsland(island2, island2Size);
    int bestIsland3PerformerIndex = getBestPerformerOfIsland(island3, island3Size);
    int bestIsland4PerformerIndex = getBestPerformerOfIsland(island4, island4Size);

    // put them in virtual boats
    chromosome migratorFromIsland1 = island1[bestIsland1PerformerIndex];
    chromosome migratorFromIsland2 = island2[bestIsland2PerformerIndex];
    chromosome migratorFromIsland3 = island3[bestIsland3PerformerIndex];
    chromosome migratorFromIsland4 = island4[bestIsland4PerformerIndex];

    /*
    Serial.println("best perfomrers from each island to be sent away:");
    Serial.print(bestIsland1PerformerIndex); Serial.print(": ");
    Serial.println(migratorFromIsland1.toString());
    Serial.print(bestIsland2PerformerIndex); Serial.print(": ");
    Serial.println(migratorFromIsland2.toString());
    Serial.print(bestIsland3PerformerIndex); Serial.print(": ");
    Serial.println(migratorFromIsland3.toString());
    Serial.print(bestIsland4PerformerIndex); Serial.print(": ");
    Serial.println(migratorFromIsland4.toString());
    Serial.println();
    */

    // do the actual migration by letting the boats arrive
    // start with randoms from elite island, to prevent sending back the new migrant
    island1[bestIsland1PerformerIndex] = migratorToIsland1;
    island2[bestIsland2PerformerIndex] = migratorToIsland2;
    island3[bestIsland3PerformerIndex] = migratorToIsland3;
    island4[bestIsland4PerformerIndex] = migratorToIsland4;

    // send best perfomer from each island to the elite island
    islandElite[randomIndexes[0]] = migratorFromIsland1;
    islandElite[randomIndexes[1]] = migratorFromIsland2;
    islandElite[randomIndexes[2]] = migratorFromIsland3;
    islandElite[randomIndexes[3]] = migratorFromIsland4;

    /*
    Serial.println("print of each island to verify that migration was successful");

    Serial.println("Island1:");
    for (int i = 0; i < island1Size; i++)
    {
        Serial.print(i);
        Serial.print(": ");
        Serial.println(island1[i].toString());
    }
    Serial.println();

    Serial.println("Island2:");
    for (int i = 0; i < island2Size; i++)
    {
        Serial.print(i);
        Serial.print(": ");
        Serial.println(island2[i].toString());
    }
    Serial.println();

    Serial.println("Island3:");
    for (int i = 0; i < island3Size; i++)
    {
        Serial.print(i);
        Serial.print(": ");
        Serial.println(island3[i].toString());
    }
    Serial.println();

    Serial.println("Island4:");
    for (int i = 0; i < island4Size; i++)
    {
        Serial.print(i);
        Serial.print(": ");
        Serial.println(island4[i].toString());
    }
    Serial.println();

    Serial.println("Island Elite:");
    for (int i = 0; i < islandEliteSize; i++)
    {
        Serial.print(i);
        Serial.print(": ");
        Serial.println(islandElite[i].toString());
    }
    Serial.println();
    */
    
}


void updateGeneraion()
{
    Serial.print("generation ");
    Serial.print(generation);
    Serial.println(" has ended");
    
    Serial.println("print of each island before update");

    Serial.println("Island1:");
    for (int i = 0; i < island1Size; i++)
    {
        Serial.print(i);
        Serial.print(": ");
        Serial.println(island1[i].toString());
    }
    Serial.println();

    Serial.println("Island2:");
    for (int i = 0; i < island2Size; i++)
    {
        Serial.print(i);
        Serial.print(": ");
        Serial.println(island2[i].toString());
    }
    Serial.println();

    Serial.println("Island3:");
    for (int i = 0; i < island3Size; i++)
    {
        Serial.print(i);
        Serial.print(": ");
        Serial.println(island3[i].toString());
    }
    Serial.println();

    Serial.println("Island4:");
    for (int i = 0; i < island4Size; i++)
    {
        Serial.print(i);
        Serial.print(": ");
        Serial.println(island4[i].toString());
    }
    Serial.println();

    Serial.println("Island Elite:");
    for (int i = 0; i < islandEliteSize; i++)
    {
        Serial.print(i);
        Serial.print(": ");
        Serial.println(islandElite[i].toString());
    }
    Serial.println();


    childMutationsInCurrentGen = 0;
    generalMutationsInCurrentGen = 0;

    // update all five island

    currentIslandID = ISLAND1_ID; // used for island origin in new population
    updateIsland(island1, island1Size);

    currentIslandID = ISLAND2_ID;
    updateIsland(island2, island2Size);

    currentIslandID = ISLAND3_ID;
    updateIsland(island3, island3Size);

    currentIslandID = ISLAND4_ID;
    updateIsland(island4, island4Size);

    currentIslandID = ISLANDELITE_ID;
    updateIsland(islandElite, islandEliteSize);

    
    //Serial.println(childMutationsInCurrentGen);
    //Serial.println(generalMutationsInCurrentGen);
    

    // do migration after all islands are updated
    doMigration();

    generation++;


    Serial.println("print of each island after update");

    Serial.println("Island1:");
    for (int i = 0; i < island1Size; i++)
    {
        Serial.print(i);
        Serial.print(": ");
        Serial.println(island1[i].toString());
    }
    Serial.println();

    Serial.println("Island2:");
    for (int i = 0; i < island2Size; i++)
    {
        Serial.print(i);
        Serial.print(": ");
        Serial.println(island2[i].toString());
    }
    Serial.println();

    Serial.println("Island3:");
    for (int i = 0; i < island3Size; i++)
    {
        Serial.print(i);
        Serial.print(": ");
        Serial.println(island3[i].toString());
    }
    Serial.println();

    Serial.println("Island4:");
    for (int i = 0; i < island4Size; i++)
    {
        Serial.print(i);
        Serial.print(": ");
        Serial.println(island4[i].toString());
    }
    Serial.println();

    Serial.println("Island Elite:");
    for (int i = 0; i < islandEliteSize; i++)
    {
        Serial.print(i);
        Serial.print(": ");
        Serial.println(islandElite[i].toString());
    }
    Serial.println();
}