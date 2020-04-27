#ifndef VBAGAGE_HPP
#define VBAGAGE_HPP

class vBagage {

    public:

        vBagage(float volume);
        virtual void calculerVolume() = 0;
        float getVolume();

    private:

        float volume_;

};

#endif