#ifndef AwtrixGolApplication_h
#define AwtrixGolApplication_h

#include <IApplication.h>

class GolApp : public IApplication
{
    private:
        
        const unsigned long UpdateThreshold = 30000l;
    public:
       void gameOfLifeInit();
        void render(DisplayManager&) override;
        void update() override;
};

#endif
