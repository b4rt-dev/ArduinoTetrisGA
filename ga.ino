

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

        island1[i].score        = esp_random() %20; // TODO remove this debugging
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

    wLines         = island1[currentChromosomeID].wLines;
    wDeltaHeight   = island1[currentChromosomeID].wDeltaHeight;
    wHoles         = island1[currentChromosomeID].wHoles;
    wBigWells      = island1[currentChromosomeID].wBigWells;
    wMaxHoleDist   = island1[currentChromosomeID].wMaxHoleDist;
    wBumpiness     = island1[currentChromosomeID].wBumpiness;

    updateGeneraion();
    while (true) delay(100);
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

void makeRandomPairIndexes(int indexes[], int arraySize)
{
    for (int i=0; i < arraySize; i++) {
       int n = random(0, arraySize);
       int temp = indexes[n];
       indexes[n] =  indexes[i];
       indexes[i] = temp;
    }
}


// generates crossover from two given parents (indices) on a given island
chromosome crossOver(chromosome island[], int parent2, int parent1)
{
    chromosome child;

    child.score        = 0;
    child.lines        = 0;

    child.originGeneration = generation + 1;
    child.originIsland     = 0; //TODO

    if (esp_random() % 2 == 1) 
        child.wLines = island[parent1].wLines;
    else
        child.wLines = island[parent2].wLines;

    if (esp_random() % 2 == 1) 
        child.wDeltaHeight = island[parent1].wDeltaHeight;
    else
        child.wDeltaHeight = island[parent2].wDeltaHeight;

    if (esp_random() % 2 == 1) 
        child.wHoles = island[parent1].wHoles;
    else
        child.wHoles = island[parent2].wHoles;

    if (esp_random() % 2 == 1) 
        child.wBigWells = island[parent1].wBigWells;
    else
        child.wBigWells = island[parent2].wBigWells;

    if (esp_random() % 2 == 1) 
        child.wMaxHoleDist = island[parent1].wMaxHoleDist;
    else
        child.wMaxHoleDist = island[parent2].wMaxHoleDist;

    if (esp_random() % 2 == 1) 
        child.wBumpiness = island[parent1].wBumpiness;
    else
        child.wBumpiness = island[parent2].wBumpiness;

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

void selection(chromosome island[], int islandSize, int selectedChromosomes[])
{
    // print island population
    for (int i = 0; i < islandSize; i++)
    {
        Serial.println(island[i].toString());
    }
    Serial.println();


    // create random indexes used for creating pairs
    int pairIndexes[islandSize];
    for (int i = 0; i < islandSize; i++)
    {
        pairIndexes[i] = i;
    }
    makeRandomPairIndexes(pairIndexes, islandSize);
    

    // print indexes
    /*
    for (int i = 0; i < islandSize; i++)
    {
        Serial.print(pairIndexes[i]);
        Serial.print(" ");
    }
    Serial.println();
    */

    // for each pair, select the fittest
    int winners[islandSize/2];
    for (int i = 0; i < (islandSize/2); i++)
    {
        Serial.print(pairIndexes[i*2]);
        Serial.print(" ");
        Serial.print(pairIndexes[i*2 + 1]);
        Serial.print(" winner: ");
        Serial.println(getFittest(island, pairIndexes[i*2], pairIndexes[i*2 + 1]));
        winners[i] = getFittest(island, pairIndexes[i*2], pairIndexes[i*2 + 1]);
    }

    // print winners
    /*
    for (int i = 0; i < (islandSize/2); i++)
        Serial.println(winners[i]);
    */

    // the winners (parents) are already randomized, so no need for that anymore

    chromosome offspring[islandSize/4];
    for (int i = 0; i < (islandSize/4); i++)
    {
        offspring[i] = crossOver(island, winners[i*2], winners[i*2 + 1]);
        Serial.print(winners[i*2]);
        Serial.print(" ");
        Serial.print(winners[i*2 + 1]);
        Serial.print(" child: ");
        Serial.println(offspring[i].toString());
    }

    for (int i = 0; i < (islandSize/4); i++)
        Serial.println(offspring[i].toString());

}


void updateIsland1()
{
    // do selection
    int selectedChromosomes[island1Size/2];
    selection(island1, island1Size, selectedChromosomes);

}

void updateGeneraion()
{
    updateIsland1();
}