#ifndef NORMAL_H
#define NORMAL_H

#define NORMAL_SIZE 65160

class Normal{
private:
    Normal(){}

    static float normal[NORMAL_SIZE][3];

    static class _init{
        public: _init();
    } _normal_initializer;
public:
    static float x(int at){
        if(0<at and at<NORMAL_SIZE){
            return normal[at][0];
        }else{
            return 0;
        }
    }
    static float y(int at){
        if(0<at and at<NORMAL_SIZE){
            return normal[at][1];
        }else{
            return 0;
        }
    }
    static float z(int at){
        if(0<at and at<NORMAL_SIZE){
            return normal[at][2];
        }else{
            return 0;
        }
    }
};

#endif // NORMAL_H
