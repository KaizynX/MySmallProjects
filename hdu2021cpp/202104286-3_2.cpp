/*
 * @Author: Kaizyn
 * @Date: 2021-04-28 11:30:46
 * @LastEditTime: 2021-04-28 11:30:46
 */

    class CRAFT{
        protected:
            double speed;
        public:
            CRAFT(double a):speed(a)
            {cout<<"创建航行器(速度: "<<speed<<")"<<endl;}


            virtual ~CRAFT()
            {cout<<"销毁航行器(速度: "<<speed<<")"<<endl;}
            virtual void Show()
            {cout<<"航行(速度: "<<speed<<")"<<endl;}
};
class PLANE:virtual public CRAFT{
        protected:
            double wi;
        public:
            PLANE(double a,double b):CRAFT(a),wi(b)
            {cout<<"创建飞机(翼展: "<<wi<<")"<<endl;}
            ~PLANE()
            {cout<<"销毁飞机(翼展: "<<wi<<")"<<endl;}
            void Show()
            {cout<<"航行(速度: "<<speed<<", 翼展: "<<wi<<")"<<endl;}
};
class SHIP:virtual public CRAFT{
        protected:
            double de;
        public:
            SHIP(double a,double b):CRAFT(a),de(b)
            {cout<<"创建船(吃水: "<<de<<")"<<endl;}
             ~SHIP()
            {cout<<"销毁船(吃水: "<<de<<")"<<endl;}
            void Show(){
                cout<<"航行(速度: "<<speed<<", 吃水: "<<de<<")"<<endl;
            }
};
class SEAPLANE:public PLANE,public SHIP{
        public:
            SEAPLANE(double a,double b,double c):PLANE(a,b),SHIP(a,c),CRAFT(a)
            {
                cout<<"创建水上飞机"<<endl;
            }
            ~SEAPLANE()
            {cout<<"销毁水上飞机"<<endl;}
            void Show(){
            cout<<"航行(速度: "<<PLANE::speed <<", 翼展: "<<wi<<", 吃水: "<<de<<")"<<endl;
            }
};
