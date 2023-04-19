#ifndef GLOBAL_H
#define GLOBAL_H


class global
{
public:
    global();

    static float c0;
    static float c1;
    static float c2;
    static float c3;
    static float c4;
    static float c5;
    static float c6;

    static float c7;
    static float c8;
    static float c9;


    static float c17;
    static float c18;
    static float c19;

    static float c10;
    static float c11;
    static float c12;
    static float c13;
    static float c14;
    static float c15;
    static float c16;

    static float c20;



    static float kp;
    static float ki;
    static float kd;
    static float integral_top;
    static float integral_down;
    static float I1;
    static float Q;
    static float R;



    static float model_n;

    static int listen_signal;

    static double sendcount;

    //画图传递值
   static int p0,p1,p2,p3,p4,p5,p6,p7,p8,p9,p10,p11,p12,p13,p14,p15,p16,p17,p18,p19,p20;
};
#endif // GLOBAL_H
//global::model_n;//模式判断
//global::c0;//燃油计量伺服阀电压输入(V)
//global::c1;//TCM关断控制伺服阀电压输入(V)
//global::c2;//关断控制比例阀电压输入(V)
//global::c3;//二通比例调速阀电压输入(V)
//global::c4;//VSV伺服阀放大板电压输入(V)
//global::c5;//超转保护泄油阀(IO）
//global::c6;//电动关断先导阀(IO)


//global::c10;//燃油阀PID输入
//global::c11//VS PID输入
//global::c12;//TCM模式输出燃油流量设定
//global::c13;//输出燃油流量设定
//global::c14;//飞机飞行高度设定
//global::c15;//飞机飞行速度设定
//global::c16;//飞机飞行轨迹设定

//global::c7;//发动机N1转速设定
//global::c20;//发动机输出推力设定
//global::c17;//发动机工作高度设定
//global::c18;//发动机工作MA设定
//global::c19;//发动机工作温度设定
