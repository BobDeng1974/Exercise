void PolyStart(){
	Poly *p,*q;
	p = (Poly*)malloc(sizeof(Poly));
	p->next=NULL;
	cout << "一元多项式运算" << endl;

	Slove(p);
	Sort(p);
	Dis(p);
	getch();
}

void Slove(Poly *p){
	Poly *q;
	string in;
	stringstream ss;
	int n,coe,ind;
	char c='#';
	regex pattern("(([+-]|^)\\d+[Xx]\\^\\d+)");
	
	regex pa("([+-]|^)(\\d+)([+-]|$)");
	string rep="$1$2x^0$3";

	//regex patt("([+-]|^)(\\d+)([Xx])([+-]|$)");
	//string replace="$1$2$3^1$4";
	regex patt("([Xx])([+-]|$)");
	string replace="$1^1$2";

	regex patter("([+-]|^)([Xx])");
	string re = "$1$101$2$3";
	
	for (n = 0; n < 2; n++){
		cout << "请输入多项式:";
		cin >> in;

		in = regex_replace(in, patter, re);
		//格式化字符串:x
		in=regex_replace(in, patt, replace);

		in = regex_replace(in, pa, rep);
		//cout << in << endl;

		 for (std::sregex_iterator it(in.cbegin(), in.cend(), pattern), q; it != q; ++it){
			//cout << "str: " << it->format("$1") << "\n";
			//cout << it->format("$1")[0];

			ss<<it->format("$1");
			if(it->format("$1")[0]=='+'||it->format("$1")[0] == '-') ss>>c;
			ss>>coe;
			if(c=='-') coe=-coe;
			ss>>c;ss>>c;
			ss>>ind;
			//cout<<coe<<endl<<ind<<endl;
			ss.clear();

			Process(p,coe,ind);
		}
		//if(!IsExt()) p = (Poly*)malloc(sizeof(Poly));
	}
}

bool IsExt(int n,Poly *p){
	Poly *q;
	q=p;
	while(q!=NULL){
		if(n==q->ind) return true;
		q=q->next;
	}
	return false;
}

void Process(Poly *p,int coe,int ind){
	Poly *q;
	//不存在该指数
	if(!IsExt(ind,p)) {
		q = (Poly*)malloc(sizeof(Poly));
		q->coe=coe;
		q->ind=ind;
		q->next=NULL;
		while(p->next!=NULL) p=p->next;
		p->next=q;
	}
	else{
		q=p->next;
		while(ind!=q->ind) q=q->next;
		q->coe +=coe;
	}
}

void Dis(Poly *p){
	Poly *q=p;
	int num=0;
	cout<<"多项式结果为:";
	for(q=q->next;q!=NULL;q=q->next){
		if(q->coe!=0){
			num++;
			if(num>1){
				if(q->coe<0) cout<<"-";
				else cout<<"+";
			}

			if(abs(q->coe)!=1) cout<<abs(q->coe);
			else if(q->ind==0) cout<<abs(q->coe);

			if (q->ind == 1)
				cout<<"x";
			else if(q->ind!=0)
				cout << "x^" << q->ind;
			//if (q->ind == 1)
			//	cout << abs(q->coe) << "x";
			//else if (q->ind == 0)
			//	cout << abs(q->coe);
			//else
			//	cout << abs(q->coe) << "x^" << q->ind;
		}
	}
	if(num==0) cout<<0<<endl;
}

void Sort(Poly *p){
	Poly *pre,*max,*temp,*j,*inpre,*maxpre,*q;
	int flag;

	pre = p;
	for (q = p->next; q != NULL; q = pre->next->next,pre=pre->next){
		flag=0;
		max = q;
		inpre = pre;
		for (j = q; j != NULL; j = j->next,inpre=inpre->next){
			if (j->ind > max->ind){
				flag=1;
				max = j;
				maxpre = inpre;
			}	
		}

		if(flag==1){
			pre->next = max;
			maxpre->next = q;
			temp = max->next;
			max->next = q->next;
			q->next = temp;
		}
	}
}
