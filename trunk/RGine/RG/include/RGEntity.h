#ifndef RGENTITY_H
#define RGENTITY_H


class RGEntity
{
    public:
        RGEntity();
        virtual ~RGEntity();

        virtual void render() = 0;
    protected:
    private:
};

#endif // RGENTITY_H
