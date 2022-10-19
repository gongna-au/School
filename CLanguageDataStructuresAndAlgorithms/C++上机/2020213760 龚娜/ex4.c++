#include<iostream>
#include <math.h>
using namespace std;


class Rational {
     
	public:
        int numerator;//molecule
        int denominator;//Denominator


    //Constructor
    Rational (int nume=1,int denom=1);

    //化简
    void simplify(){
        int i,j;
        if (numerator==0){
            denominator=1;
            return;
        }
        if (abs(numerator)>abs(denominator)){
            j=denominator;
        }else{
            j=numerator;
        }

        if(j<0){
            j=abs(j);
        }

        for(i=j;i>1;i--){
            if(denominator%i==0&&numerator%i==0){
                denominator=denominator/i;
                numerator=numerator/i;
                return;
            }
        }
    }

    //通分
    void reduction(Rational second){
        numerator=numerator*second.denominator;
        denominator=denominator*second.denominator;
    }


	int getNumerator()//Acquire Molecules
    {
        return numerator;
    }

    int getDenominator()//Get denominator
    {
        return denominator;
    }

     Rational add( Rational second)//addition
    {
        Rational temp;
        temp.numerator=numerator*second.denominator+second.numerator*denominator;
        temp.denominator=denominator*second.denominator;
        temp.simplify();
        return temp;
    }


    Rational subtract(Rational second)//subtraction
    {
        Rational temp;
        temp.numerator = numerator * second.denominator - second.numerator * denominator;
        temp.denominator= denominator * second.denominator;
        temp.simplify();
        return  temp;
    }


    Rational multiply(Rational second)//multiplication
    {
        Rational temp;
        temp.numerator= numerator * second.numerator;
        temp.denominator = denominator * second.denominator;
        temp.simplify();
        return  temp;
    }


     Rational divide(Rational second)//division
    {
        Rational temp;
        temp.numerator = numerator * second.denominator;
        temp.denominator = denominator * second.numerator;
        temp.simplify();
        return temp ;
    }

    //Determine equality
    bool equal(Rational second) 
    {
        if ((numerator == second.numerator)&&(denominator == second.denominator)) {
            return true;
        } else {
            return false;
        }
    }


     int intValue()//Return Integer
    {
        return numerator / denominator;
    }


     string toString()//Return string
    {
        if(denominator==1){

            return numerator+"";
        }
        return numerator + "/" +denominator;
    }



    //声明运算符重载
    friend Rational operator+( Rational &a,Rational &b);
    friend Rational operator-( Rational &a,Rational &b);
    friend Rational operator*( Rational &a,Rational &b);
    friend Rational operator/( Rational &a,Rational &b);

    int & operator[]( int index){
        if(index==0){
            return numerator;

        }
        if(index==1){
            return denominator;
        }
    }

    friend  Rational &operator-=(Rational &a, const Rational &b);
    friend  Rational &operator+=(Rational &a, const Rational &b);
    friend  Rational &operator*=(Rational &a, const Rational &b);
    friend  Rational &operator/=(Rational &a, const Rational &b);

    friend Rational operator++( Rational &a);
    friend Rational operator++( Rational &a,int );

    friend Rational operator--( Rational &a);
    friend Rational operator--( Rational &a,int );



    bool operator>( Rational &c);
    bool operator<( Rational &c);

    bool operator==( Rational &c);
    bool operator!=( Rational &c);
    bool operator>=( Rational &c);
    bool operator<=( Rational &c);

    void display(){
        simplify();
        if(denominator==1){
            cout << numerator;
        }else if(numerator==0){
            cout << '0';
        }
        else{
            cout << numerator << '/' << denominator;
        }

    }
};


Rational::Rational (int nume,int denom){
        denominator=denom;
        numerator=nume;
}





//分数相加
Rational  operator+( Rational &a,Rational &b){
     Rational temp(a.numerator,a.denominator);
     return temp.add(b);
     
}
// 分数相减
Rational  operator-( Rational &a,Rational &b){
     Rational temp(a.numerator,a.denominator);
     return temp.subtract(b);
}

// 分数相乘
Rational  operator*(Rational &a,Rational &b){
     Rational temp(a.numerator,a.denominator);
     return temp.multiply(b);
}
  
Rational  operator/(Rational &a,Rational &b){
    Rational temp(a.numerator,a.denominator);
     return temp.divide(b);
}




bool Rational:: operator>( Rational &c){
    //this
    Rational thistemp(numerator,denominator);
    //ctemp
    Rational ctemp(c.numerator,c.denominator);
    //temp
    Rational temp(c.numerator,c.denominator);

    temp.reduction(thistemp);
    thistemp.reduction(ctemp);
    if(thistemp.numerator> temp.numerator){
        return true;
    }else{
        return false;
    }
}
bool Rational:: operator<( Rational &c){
    //this
    Rational thistemp(numerator,denominator);
    //ctemp
    Rational ctemp(c.numerator,c.denominator);
    //temp 
    Rational temp(c.numerator,c.denominator);

    temp.reduction(thistemp);
    thistemp.reduction(ctemp);
    if(thistemp.numerator< temp.numerator){
        return true;
    }else{
        return false;
    }
}
bool Rational:: operator==( Rational &c){
    //this
    Rational thistemp(numerator,denominator);
    //ctemp
    Rational ctemp(c.numerator,c.denominator);
    //temp 
    Rational temp(c.numerator,c.denominator);

    temp.reduction(thistemp);
    thistemp.reduction(ctemp);
    if(thistemp.numerator == temp.numerator){
        return true;
    }else{
        return false;
    }

}
bool Rational:: operator!=( Rational &c){
    //this
    Rational thistemp(numerator,denominator);
    //ctemp
    Rational ctemp(c.numerator,c.denominator);
    //temp 
    Rational temp(c.numerator,c.denominator);

    temp.reduction(thistemp);
    thistemp.reduction(ctemp);
    if(thistemp.numerator!= temp.numerator){
        return true;
    }else{
        return false;
    }

}
bool Rational:: operator>=( Rational &c){
    //this
    Rational thistemp(numerator,denominator);
    //ctemp
    Rational ctemp(c.numerator,c.denominator);
    //temp 
    Rational temp(c.numerator,c.denominator);

    temp.reduction(thistemp);
    thistemp.reduction(ctemp);
    if(thistemp.numerator>= temp.numerator){
        return true;
    }else{
        return false;
    }
}
bool Rational:: operator<=( Rational &c){
    //this
    Rational thistemp(numerator,denominator);
    //ctemp
    Rational ctemp(c.numerator,c.denominator);
    //temp 
    Rational temp(c.numerator,c.denominator);

    temp.reduction(thistemp);
    thistemp.reduction(ctemp);
    if(thistemp.numerator <=  temp.numerator){
        return true;
    }else{
        return false;
    }

}

Rational& operator+=(Rational &a, Rational &b){
    Rational temp;
    temp=a.add(b);
    a.numerator=temp.numerator;
    a.denominator=temp.denominator;
    return a;
}
Rational& operator-=( Rational &a, Rational &b){
    Rational temp;
    temp=a.subtract(b);
    a.numerator=temp.numerator;
    a.denominator=temp.denominator;
    return a;
    
}
Rational& operator*=(Rational &a, Rational &b){
    Rational temp;
    temp=a.multiply(b);
    a.numerator=temp.numerator;
    a.denominator=temp.denominator;
    return a;
}

Rational& operator/=(Rational &a, Rational &b){
    Rational temp;
    temp=a.divide(b);
    a.numerator=temp.numerator;
    a.denominator=temp.denominator;
    return a;
}


//前置++
Rational operator++( Rational &a){
    Rational temp;
    temp=a.add(1);
    a.numerator=temp.numerator;
    a.denominator=temp.denominator;

    return temp;

}

//前置--
Rational operator--( Rational &a){
    Rational temp;
    temp=a.subtract(1);
    a.numerator=temp.numerator;
    a.denominator=temp.denominator;

    return temp;

}

//后置++
Rational operator++(  Rational &a,int ){
    Rational temp1,temp2;

    temp1.numerator=a.numerator;
    temp1.denominator=a.denominator;

    temp2=a.add(1);
    a.numerator=temp2.numerator;
    a.denominator=temp2.denominator;

    return temp1;

}


//后置--
Rational operator--( Rational &a){
    Rational temp1,temp2;

    temp1.numerator=a.numerator;
    temp1.denominator=a.denominator;

    temp2=a.subtract(1);
    a.numerator=temp2.numerator;
    a.denominator=temp2.denominator;

    return temp1;

}


// 程序的主函数
    int main( )
    {
        Rational rational(3,6);
   
    }
