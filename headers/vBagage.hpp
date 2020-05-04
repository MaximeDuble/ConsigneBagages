#ifndef VBAGAGE_HPP
#define VBAGAGE_HPP

class vBagage {

    public:

        vBagage(float volume);
        vBagage();
        virtual float calculerVolume() const = 0;
        float getVolume() const;

    protected:

        float volume_;

};

#endif