#ifndef NORMAL_H
#define NORMAL_H

class Normal{
private:
    Normal(){}

    static float normal[181][360][3];

    static class _init{
        public: _init();
    } _normal_initializer;
public:
    static float x(int a, int t){
        if(a>=0 and a<181 and t>=0 and t<360){
            return normal[a][t][0];
        }else{
            return 0;
        }
    }
    static float y(int a, int t){
        if(a>=0 and a<181 and t>=0 and t<360){
            return normal[a][t][1];
        }else{
            return 0;
        }
    }
    static float z(int a, int t){
        if(a>=0 and a<181 and t>=0 and t<360){
            return normal[a][t][2];
        }else{
            return 0;
        }
    }
};

#endif // NORMAL_H
