/***********************************************************************
Matr.-Nr:                     3104154
Nachname/Surname:             Alsabbagh
Vorname/Given name:           Ibrahim
Uni-Email:                    ibrahim.alsabbagh@stud.uni-due.de
Studiengang/Course of studis: software Engineering ISE
***********************************************************************/

#include<bits/stdc++.h>
using namespace std;
class Date{
private:
	int year;
	int month;
	int day;
public:
	Date operator +(int n)
	{
		const int DaysinMonth[12]={31,28,31,30,31,30,31,31,30,31,30,31};
		Date result;
		result.day=day+n,result.month=month,result.year=year;
		if(day+n>DaysinMonth[month-1])
		{
			result.day=day+n-DaysinMonth[month-1];
			result.month++;
			if(result.month>12)
			{
				result.month-=12;
				result.year++;
			}
		}
		return result;
	}
    friend istream &operator>>( istream  &ip, Date &my_date ) {
    	char garbage;
       ip>>my_date.year>>garbage>>my_date.month>>garbage>>my_date.day;
       return ip;
    }
    friend ostream &operator<<( ostream &op, const Date &my_date ) {
    	string my="";
    	my=to_string(my_date.year)+"-";
       if(my_date.month<10)
    	   my=my+"0";
       my=my+to_string(my_date.month)+"-";
       if(my_date.day<10)
    	   my=my+"0";
       my=my+to_string(my_date.day);
       return op<<my;
    }

};
enum  Board{
	breakfast=10,
	no_meals=0,
	half_board=20,
	all_inclusive=50
};
double get_price(Board board){return (double)board;}
ostream &operator<<(ostream &op, const Board value)
{
	if(value==all_inclusive)
		op<<"all inclusive ("<<get_price(all_inclusive)<<" EUR/day and person)\n";
	else if(value==breakfast)
		op<<"breakfast ("<<get_price(breakfast)<<" EUR/day and person)\n";
	else if(value==no_meals)
		op<<"no meals\n";
	else
		op<<"half board ("<<get_price(half_board)<<" EUR/day and person)\n";
	return op;
}
class Accomodation{
private:
	string location;
	Date arrival;
	int nights,singles,doubles;
	double priceNightSingle,priceNightDouble,priceOneDayParking;
	Board board;
	bool parking;

public:
	Accomodation(double pns,double pnd,double p0p)
	{
		priceNightSingle=pns;
		priceNightDouble=pnd;
		priceOneDayParking=p0p;
	}
	~Accomodation()
	{
		string loc=location;
		int ng=singles+2*doubles;
		Date dt=arrival;
		cout<<"destructor Accomodation "<<loc<<" at "<<dt<<" for "<<ng<<" guests done\n";
	}
	Date get_arrival(){return arrival;}
	Date get_checkout(){return arrival+nights;}
	int get_guests(){return singles+2*doubles;}
	double get_price()
	{
		double price_per_night=0;
		price_per_night+=(double)priceOneDayParking*parking;
		price_per_night+=(double)singles*priceNightSingle;
		price_per_night+=(double)doubles*priceNightDouble;
		price_per_night+=(double)get_guests()*(double)board;
		return (double)nights*price_per_night;
	}
	void ask_data()
	{
		cout<<"location of accomodation: ";cin>>location;
		cout<<"arrival on (yyyy-mm-dd): ";cin>>arrival;
		cout<<"how many nights (maximum 4 weeks): ";cin>>nights;
		cout<<"how many single bed rooms ("<<priceNightSingle<<" EUR/night): ";cin>>singles;
		cout<<"how many double bed rooms ("<<priceNightDouble<<" EUR/night): ";cin>>doubles;
		char for_board,for_parking;
		cout<<"a all inclusive ("<<(double)(all_inclusive)<<" EUR/day)\n";
		cout<<"b breakfast     ("<<(double)(breakfast)<<" EUR/day)\n";
		cout<<"h half board    ("<<(double)(half_board)<<" EUR/day)\n";
		cout<<"n no meals\n";
		cout<<"your choice: ";
		cin>>for_board;
		if(for_board=='n')
			board=no_meals;
		else if(for_board=='h')
			board=half_board;
		else if(for_board=='b')
			board=breakfast;
		else
			board=all_inclusive;
		cout<<"with parking place ("<<priceOneDayParking<<" EUR/day; y(es) or n(o)): ";cin>>for_parking;
		parking=(bool)(for_parking=='y');
		cout<<"price: "<<get_price()<<" EUR\n";
	}
	void print()
	{
		cout<<"accomodation at:    "<<location<<"\n";
		cout<<"number of guests:   "<<get_guests()<<"\n";
		cout<<"number of nights:   "<<nights<<"\n";
		cout<<"check-in date:      "<<arrival<<"\n";
		cout<<"check-out date:     "<<get_checkout()<<"\n";
		cout<<"single bed room(s): "<<singles<<" ("<<priceNightSingle<<" EUR/night)\n";
		cout<<"double bed room(s): "<<doubles<<" ("<<priceNightDouble<<" EUR/night)\n";
		cout<<"board:              "<<board;
		cout<<"parking:            ";
		if(parking)
			cout<<"included ("<<priceOneDayParking<<" EUR/day)\n";
		else
			cout<<"no parking place booked\n";
		cout<<"price accomodation: "<<get_price()<<"\n";
	}

};
class  Transport{
public:
	virtual ~Transport(){cout<<"destructor Transport done\n";}
	virtual bool  includedTransfer(){return false;}
	virtual double get_price()=0;
	virtual void print()=0;
};
class SelfTravel: public Transport{
public:
	SelfTravel(){}
	virtual ~SelfTravel(){cout<<"destructor SelfTravel done\n";}
	virtual double get_price(){return 0.00;}
	virtual void print(){cout<<"self travel ";}
};
class PublicTransport:public Transport{
protected:
	Date departure;
	string code;
	string from;
	string to;
	double priceOneSeat;
	bool firstClass;
public:
	PublicTransport(Date departure_,string code_,string from_,string to_,double price,bool first_class=false)
	{
		departure=departure_;
		code =code_;
		from=from_;
		to=to_;
		priceOneSeat=price;
		firstClass=first_class;
	}
	virtual ~PublicTransport()
	{
		cout<<"destructor PublicTransport "<<code<<" at "<<departure
				<<" from "<<from<<" to "<<to<<" done\n";
	}
	virtual void print()
	{
		cout<<departure<<" "<<code<<" from "<<from<<" to "<<to<<" ";
		if(firstClass)
			cout<<"first class ";
		cout<<"("<<get_price()<<" EUR/person) ";
	}
};
Date xxx;
class Flight:public PublicTransport{
protected:
	bool transfer;
public:
	Flight(Date departure_,string code_,string from_,string to_,double price,bool first_class=false,bool trnsfer_
			=1) : PublicTransport(xxx,"","","",0.00,false)
	{
		departure=departure_;
		code =code_;
		from=from_;
		to=to_;
		priceOneSeat=price;
		firstClass=first_class;
		transfer=trnsfer_;
	}
	virtual ~Flight(){cout<<"destructor Flight done\n";}
	virtual bool includedTransfer(){return transfer;}
	virtual double get_price(){return (double)(priceOneSeat*(1+firstClass));}
	virtual void print()
	{
		cout<<"flight ";
		PublicTransport::print();
	}
};
class Train:public PublicTransport{
protected:
	bool transfer;
public:
	Train(Date departure_,string code_,string from_,string to_,double price,bool first_class=false,bool trnsfer_
			=1) : PublicTransport(xxx,"","","",0.00,false)
	{
		departure=departure_;
		code =code_;
		from=from_;
		to=to_;
		priceOneSeat=price;
		firstClass=first_class;
		transfer=trnsfer_;
	}
	virtual ~Train(){cout<<"destructor Train done\n";}
	//virtual bool includedTransfer(){return transfer;}
	virtual double get_price(){return (double)(priceOneSeat*(1+0.5*(double)firstClass));}
	virtual void print()
	{
		cout<<"train ";
		PublicTransport::print();
	}
};
class Request{
private:
	unsigned int no;
	static unsigned int lastNo;
	Request* next;
	Accomodation* accomodation;
	Transport* transportReturn;
	Transport* transportOutward;
public:
	Request(Accomodation* accomodation_,Request* request=NULL,Transport* outward=NULL,Transport* Return=NULL)
	{
		accomodation=accomodation_;
		next=request;
		lastNo+=1;
		no=lastNo;
		transportOutward=outward;
		transportReturn=Return;
	}
	~Request()
	{
		delete accomodation;
		delete transportOutward;
		delete transportReturn;
		cout<<"destructor Request "<<no<<" done\n";
	}
	int get_no(){return no;}
	Request* get_next(){return next;}
	void set_next(Request* tmp){next=tmp;}
	double get_price()
	{
		double total_price=accomodation->get_price();
		total_price+=accomodation->get_guests()*(transportOutward->get_price()+
				transportReturn->get_price());
		return total_price;
	}
	void print()
	{
		cout<<"********REQUEST NO: "<<no<<"********\n";
		accomodation->print();
		cout<<"outward journey:    ";
		transportOutward->print();
		if(transportOutward->includedTransfer())
			cout<<"transfer included\n";
		else
			cout<<"no transfer\n";
		cout<<"journey back:       ";
		transportReturn->print();
		if(transportReturn->includedTransfer())
			cout<<"transfer included\n";
		else
			cout<<"no transfer\n";
		cout<<"price total:        "<<get_price()<<" EUR\n\n";
	}
};
class CallCenter{
private:
	Request* head;
public:
	CallCenter(){head=NULL;}
	void append(Request* request)
	{
		if(head==NULL)head=request;
		else
		{
			Request* tail=head;
			while(tail->get_next()!=NULL)
				tail=tail->get_next();
			tail->set_next(request);
		}
	}
	void cancel(Request* request)
	{
		Request* tail=head;
		Request* not_this=NULL;
		if(tail!=NULL&&tail==request)
		{
			head=request->get_next();
			delete tail;
		}
		else
		{
			while(tail!=NULL&&tail!=request)
			{
				not_this=tail;
				tail=tail->get_next();
			}
			if(tail==NULL)
				return;
			not_this->set_next(tail->get_next());
			delete tail;
		}
	}
	Request* get_request(int number_of_request)
	{
		Request* request=head;
		while(request!=NULL&&request->get_no()!=number_of_request)
			request=request->get_next();
		return request;
	}
	void print_all()
	{
		Request* request=head;
		while(request!=NULL)
		{
			request->print();
			request=request->get_next();
		}
		cout<<"\n";
	}
};
void call_main_menu()
{
	cout<<"CALL CENTER BOOKING REQUEST\n";
	cout<<"0 end\n";
	cout<<"1 new reservation request standard\n";
	cout<<"2 new reservation request superior\n";
	cout<<"3 show reservation request\n";
	cout<<"4 show all reservation requests\n";
	cout<<"your choice: ";
}
unsigned int Request::lastNo=0;
int main()
{
	CallCenter my_center;
	int request;
	cout<<fixed<<setprecision(2);
	while(true)
	{
		call_main_menu();
		cin>>request;
		if(request==0)
			break;
		if(request==1||request==2)
		{
			Accomodation* accomodation_;
			Transport* OUTWARD;
			Transport* RETURN;
			if(request==1)
				accomodation_=new Accomodation(80,150,10);
			else
				accomodation_=new Accomodation(110,210,10);
			accomodation_->ask_data();
			Date arrival=accomodation_->get_arrival();
			Date departuer=accomodation_->get_checkout();
			string code,from,to;
			char first_class;
			double price;
			int type;
			cout<<"please choose transport outward"<<"\n";
			cout<<"0 self travel\n";
			cout<<"1 by flight\n";
			cout<<"2 by train\n";
			cout<<"your choice: ";
			cin>>type;
			if(type==0)
				OUTWARD= new SelfTravel();
			else if(type==1)
			{
				cout<<"code of flight: ";
				cin>>code;
				cout<<"airport of departure: ";
				cin>>from;
				cout<<"airport of arrival: ";
				cin>>to;
				cout<<"standard price for one passenger: ";
				cin>>price;
				cout<<"first class ((y)es or (n)o): ";
				cin>>first_class;
				OUTWARD=new Flight(arrival,code,from,to,price,first_class=='y');
			}
			else
			{
				cout<<"code of train: ";
				cin>>code;
				cout<<"main train station of departure: ";
				cin>>from;
				cout<<"main train station of arrival: ";
				cin>>to;
				cout<<"first class ((y)es or (n)o): ";
				cin>>first_class;
				cout<<"price for one passenger: ";
				cin>>price;
				OUTWARD=new Train(arrival,code,from,to,price,first_class=='y');
			}
			cout<<"please choose transport return"<<"\n";
			cout<<"0 self travel\n";
			cout<<"1 by flight\n";
			cout<<"2 by train\n";
			cout<<"your choice: ";
			cin>>type;
			if(type==0)
				RETURN= new SelfTravel();
			else if(type==1)
			{
				cout<<"code of flight: ";
				cin>>code;
				cout<<"airport of departure: ";
				cin>>from;
				cout<<"airport of arrival: ";
				cin>>to;
				cout<<"standard price for one passenger: ";
				cin>>price;
				cout<<"first class ((y)es or (n)o): ";
				cin>>first_class;
				RETURN=new Flight(departuer,code,from,to,price,first_class=='y');
			}
			else
			{
				cout<<"code of train: ";
				cin>>code;
				cout<<"main train station of departure: ";
				cin>>from;
				cout<<"main train station of arrival: ";
				cin>>to;
				cout<<"first class ((y)es or (n)o): ";
				cin>>first_class;
				cout<<"price for one passenger: ";
				cin>>price;
				RETURN=new Train(departuer,code,from,to,price,first_class=='y');
			}
			Request* REQUEST=new Request(accomodation_,NULL,OUTWARD,RETURN);
			my_center.append(REQUEST);
			cout<<"\n";
		}
		else if(request==3)
		{
			cout<<"number of reservation request: ";
			int number_of_request;
			cin>>number_of_request;
			Request* request=my_center.get_request(number_of_request);
			if(request==NULL)
				cout<<"reservation request not found\n";
			else
			{
				request->print();
				cout<<"(c)ancel this request or (n)ot: ";
				char cancel;
				cin>>cancel;
				if(cancel=='c')my_center.cancel(request);
			}
			cout<<"\n";
		}
		else if(request==4)my_center.print_all();
	}
	return 0;
}

