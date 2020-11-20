class MyObject  {

    static int instanceCounter = 0;

    int counter = 0;

    MyObject() 
    {
        instanceCounter++;
        counter = instanceCounter;
    }

}