/*
Name : Danish Mukhtar
Roll NO: 2018201016
MTECH CSE
*/


#include<stdio.h>
#include<iostream>
#include <dirent.h>
#include<termios.h>
#include <sys/types.h>
#include<stdlib.h>
#include<stack>
#include <unistd.h>
#include<string>
#define gotoxy(x,y) printf("\033[%d;%dH", (x), (y))
#include <sys/stat.h>
#include<pwd.h>
#include<vector>
#include<grp.h>
#include<algorithm>
#include<fstream>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include<unordered_map>
#define NORMALMODE 0
#define COMMANDMODE 1
#include<signal.h>



using namespace std;
void change_mode_to(int mode);
void CommandMode();
void     INThandler(int);
void copy_file(string,string);
void real_clean();
unordered_map<string,string> trash_records;
stack<string> back_history,forward_history,bkh,fkh;

int back=0;
int height = 15;
string path = "/home/danish/Desktop",pathdup;
string home = path;
struct dirent ** namelist;
struct tm *foo;
int scroll_k = 0;
struct termios initial_settings, new_settings,ppsettings;
int nn,n,start_x=3,start_y=1;
int y = 1,command_mode_height=2;
string mode_name[2]={" Normal Mode "," Command Mode"};
int mode_num=NORMALMODE;
vector<string> v;
string suc;
vector<string> display_commands;
string WHITESPACE = " \n\r\t\f\v";
int scroll_command_position=0;

int infinite_loop=0;


void pathshow(){
	gotoxy(height+4,20);
	if(pathdup.size()<55){
		cout<<"Path : ./"<<pathdup.substr(home.length());
	}
	else{ 
		cout<<"Path : ./"<<pathdup.substr(0,45)<<" ..";
	}
	gotoxy(y+start_x-1,1);
}
string getactualpath(string pathx){

	int i = pathx.size()-1;
	while(i>1){
	
		if(pathx[i]=='/'){
		break;
		}
	i--;
	}
	return pathx.substr(0,i);
}
void print_dirs(int,int);

	struct winsize w;
    

	int rows,cols;
	ofstream out;
    	
	vector<string> search_path;


void  INThandler(int sig)
{
	char  c;
	gotoxy(1,1);

	for(int j = 1;j<=height+9;j++){
		gotoxy(j,1);

		for(int j = 1;j<79;j++){

			cout<<" ";
		}
     	}
	signal(sig, SIG_IGN);

	tcsetattr(0, TCSANOW, &initial_settings); 

	real_clean();
	fflush(stdout);	
	gotoxy(1,1);

	exit(0);
}
void init_Search_Screen(){
	gotoxy(1,1);
	for(int j = 1;j<78;j++){
		cout<<" ";
	}
	gotoxy(1,1);
	cout << "\e[1m\tName\e[0m" ;
	printf("\033[1;28H");
	cout << "\e[1mPath\e[0m" ;
	
	gotoxy(2,1);
	for(int j = 1;j<78;j++){
		cout<<"=";
	}
	gotoxy(height+3,1);
	for(int i =1;i<78;i++){
		cout<<"=";
	}
	gotoxy(height+5,1);
	for(int i =1;i<78;i++){
		cout<<"=";
	}
	gotoxy(height+4,1);

	cout<<mode_name[mode_num];
	gotoxy(start_x,start_y);
}
void print_search(int j,int limit_y,string name){
	real_clean();
	change_mode_to(NORMALMODE);
	nn=search_path.size();
	n=nn;	
	n--;
	
	gotoxy(start_x,start_y);

	int numbers=j+1;
	int ini=j;
	if(nn<limit_y){
		limit_y=nn;
	}
	gotoxy(start_x,start_y);
	while(ini<limit_y){

	
		printf(" %d ",numbers);
		printf("\x1B[36m");
	
		string cc = name;
		if(cc.size()>25){
			cc=cc.substr(0,25);
			printf("%s",cc.c_str());
	
		}
		else{
	
			printf("%s",name.c_str());

		}	
		printf("\x1B[0m");

		printf("\033[%d;28H",ini-j+3);
	 //+1
		printf("%s",("."+search_path[ini].substr(home.length())).c_str());
	

		cout<<"\n";
		
	   
	    numbers++;
	    ini++;
		
	}
	gotoxy(start_x,start_y);

}
void searchConsole(int j,int limit_y,string name){

	tcgetattr(0,&initial_settings);
	new_settings = initial_settings;

	new_settings.c_lflag &= ~ECHO;

	new_settings.c_lflag &= ~ICANON;

	tcsetattr(0, TCSANOW, &new_settings); 
	init_Search_Screen();
	print_search(j,limit_y,name);
	char ch;
	gotoxy(start_x,start_y);
	int flag=0;
	y=1;
	scroll_k = 0;
	init_Search_Screen();

	while(1){
		ch = getchar();
		int s = (int)ch;
	
	
		switch(s){
		case 58:{
			flag=1;
				break;		
			}
			case 65:
			{
					
				if(y>=2){
					y--;
					gotoxy(y+start_x-1,1);//y+2,1....new change

						break;
				}
				
				if(scroll_k!=0)
				{
	
				gotoxy(start_x,start_y);
				scroll_k=scroll_k-1;

				print_search(scroll_k,height+scroll_k,name);
				gotoxy(start_x,start_y);
				
				}
				else
				{
								
				}
				break;			
			}
			//down
			case 66:{	

				if(nn>height){
				if(height-(height-y)+scroll_k<nn){
				if(y<height){
					y++;
					gotoxy(y+start_x-1,1); //y,1....y+2
					break;
				}		
				gotoxy(start_x,start_y);
				scroll_k++;
				print_search(scroll_k,height+scroll_k,name);
				gotoxy(height+start_x-1,1);//height,1
				}
				}else{
				if(y<nn)
				{
					y++;
					gotoxy(y+start_x-1,1);//shayad y,1 ///............y+2
				}	

				}
				break;			
			}
			case 68:case 127:
				{
				fflush(stdout);		
				

				y=1;
				scroll_k=0;
								
				flag=1;
				print_dirs(0,height);break;
				
			}
			case 10:{	
				
				fflush(stdout);		
				cout<<path;
				string pathre = search_path[y+scroll_k-1]+"/"+name;
				for(int k=0;k<pathre.size();k++){
					if(pathre[k]==' '){

						pathre.insert(k,1,'\\');
						k+=1;
					}
				}
				
				pid_t pid = fork();
				string path1 = pathre;

				if (pid == 0) {		
  					
					int out = open("err.log", O_RDWR|O_CREAT|O_APPEND, 0600);
    					
  					 if (-1 == out) { perror("opening cout.log"); return ; }
    					int save_out = dup(fileno(stderr));
   					if (-1 == dup2(out, fileno(stderr))) { perror("cannot redirect stdout"); return ; }
      					
  	  			  	execl("/usr/bin/xdg-open", "xdg-open", path1.c_str(), (char *)0);
						
  	  				fflush(stderr); close(out);
  			
  	  				dup2(save_out, fileno(stderr));
   

  	  				close(save_out);
  				
  					exit(1);
				}
				y=1;
				scroll_k=0;

								
				flag=1;
				print_dirs(0,height);

			break;
			}
		}
		if(flag){
			break;
		}

	}




}
void snap_shot(string pathxx,string shower)
{
	
	FILE *target;
	int i;
 
	target = fopen(pathxx.c_str(), "w"); 
	struct dirent ** list;
	int nn=scandir(pathxx.c_str(),&list,NULL,alphasort);
	
    	
    	
    	string input= "\n\n"+shower+":\n\n";
	out<< input;
	for(int i = 2;i<nn;i++){
		string ss  =" " + (string)list[i]->d_name+"   ";
		out<<ss;
	}
	

		
	
	for(int i = 2;i<nn;i++){
		string ss  =pathxx+"/"+list[i]->d_name;
		if((int)list[i]->d_type==4){
					snap_shot(ss,shower+"/"+list[i]->d_name);
		}
		
	}

	
}
void create_file(string dtr)
{
	FILE * source;
	source= fopen(dtr.c_str(), "w"); 

}

void create_directory(string filename)
{

	mkdir(filename.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);

}
void removeDirectory(string dirname){
	infinite_loop++;
	if(infinite_loop>100){
		return;		
	}

	struct dirent ** list;
	int nn=scandir(dirname.c_str(),&list,NULL,alphasort);
	
	for(int i = 2;i<nn;i++){
		string ss  =dirname+"/"+list[i]->d_name;
		if((int)list[i]->d_type==4){
			removeDirectory(ss.c_str());
			remove(ss.c_str());		
		}
		else if((int)list[i]->d_type==8){
			
			remove(ss.c_str());	
		}
	}

}

int searchfile(string pathx,string filename){
	

	struct dirent ** list;
	int nn=scandir(pathx.c_str(),&list,NULL,alphasort);
	int resuld=0,resulf = 0;
	for(int i = 2;i<nn;i++){
		if((int)list[i]->d_type==4){
			resuld = searchfile(pathx+"/"+list[i]->d_name,filename);
				
		}
		else if((int)list[i]->d_type==8){
			if(filename.compare(list[i]->d_name)==0){
				search_path.push_back(pathx);
				
				resulf=1;			
			}
		}
	}
	if(resulf==1){return 1;}
		if(resuld==1){return 1;}
		
	return 0; 
		
	 
}
void copy_directory(string dirname,string dir2,string foldername){

	infinite_loop++;
	if(infinite_loop>100){
	return;		
	}
	
	struct dirent ** list;
	int nn=scandir(dirname.c_str(),&list,NULL,alphasort);
	dir2 = dir2+"/"+foldername;	
	int status = mkdir(dir2.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
	struct stat perm;
	stat(dirname.c_str(),&perm);
	chown(dir2.c_str(),perm.st_uid,perm.st_gid);
	chmod(dir2.c_str(),perm.st_mode);
	for(int i = 2;i<nn;i++){
		if((int)list[i]->d_type==4){
			copy_directory(dirname+"/"+list[i]->d_name,dir2,list[i]->d_name);		
		}
		else if((int)list[i]->d_type==8){
			copy_file(dirname+"/"+list[i]->d_name,dir2+"/"+list[i]->d_name);
			struct stat perm;
			stat((dirname+"/"+list[i]->d_name).c_str(),&perm);
			chown((dir2+"/"+list[i]->d_name).c_str(),perm.st_uid,perm.st_gid);
			chmod((dir2+"/"+list[i]->d_name).c_str(),perm.st_mode);
		}
	}
		
	 
}

string rtrim(string s){
	size_t end = s.find_last_not_of(WHITESPACE);
	return (end==string::npos) ? "" : s.substr(0,end+1);
}

int split(string &txt, vector<string> &strs, char ch)
{
	strs.clear();
	int i = 0;
	int ip=0,which;
	while(i<txt.size()){

		if(txt[i]=='\''){
			i++;
			ip=i;
			while(txt[i]!='\''){
				if(txt[i]=='\\'){
					txt.erase(i,1);			
				}			
			i++;
			}
	
			strs.push_back(txt.substr(ip,i-ip));
			i=i+2;
			ip=i;
			which=1;
		}
	
		else if(txt[i]==' '){

			strs.push_back(txt.substr(ip,i-ip));
			i++;	
			ip=i;
			which=2;
		}else{
			i++;	
			which=3;
		}
	}
	if(which==3){
		strs.push_back(txt.substr(ip,i-ip));
	}


	return strs.size();

}

void init_Screen(){
	gotoxy(1,1);
	cout << "\e[1m\tName\e[0m" ;
	printf("\033[1;28H");
	cout << "\e[1mSize\e[0m" ;
	printf("\033[1;36H");
	cout << "\e[1mPermissions\e[0m" ;
	printf("\033[1;50H");
	cout << "\e[1mOwner & Group\e[0m" ;
	printf("\033[1;66H");
	cout << "\e[1mLast Modified\e[0m" ;
	gotoxy(2,1);
	for(int j = 1;j<78;j++){
		cout<<"=";
	}
	gotoxy(height+3,1);
	for(int i =1;i<78;i++){
		cout<<"=";
	}
	gotoxy(height+5,1);
	for(int i =1;i<78;i++){
		cout<<"=";
	}
	gotoxy(height+4,1);

	cout<<mode_name[mode_num];
	gotoxy(start_x,start_y);
}

void change_mode_to(int mode){
	mode_num = mode;
	gotoxy(height+4,1);
	
	cout<<mode_name[mode_num];
}
void print_command_mode_Scroll(int p){
	gotoxy(height+6,1);
	for(int i = 0;i<=command_mode_height+2;i++){
		gotoxy(height+6+i,1);
		for(int j=1;j<80;j++){
			cout<<" ";
		}
	}
	gotoxy(height+6,1);
	if(p==1){
		if(display_commands.size()>command_mode_height){
			scroll_command_position+=2;
		}
	}
	for(int i = scroll_command_position;i<display_commands.size();i++){
		if(i%2==0){
			cout<<"> "<<display_commands[i]<<endl;
		}else{
			cout<<"  "<<display_commands[i]<<endl;
		}
		
	}
	cout<<"> ";
}
int check_file_exists(string file_name){
int flag = 0;
for(int i=2;i<n;i++){
	if(file_name.compare(namelist[i]->d_name)==0){
			flag=namelist[i]->d_type;	
			break;		
		}
}
return flag;
}



void copy_file(string sr,string dt){

	FILE *source, *target;
	int i;
 
	source = fopen(sr.c_str(), "r"); 



	fseek(source, 0, SEEK_END);
	int length = ftell(source);

	fseek(source, 0, SEEK_SET);
	target = fopen(dt.c_str(), "w"); 


	for(i = 0; i < length; i++){
    		fputc(fgetc(source), target);
	}

	 
	fclose(source); 
	fclose(target);
}
void CommandMode(){
	print_command_mode_Scroll(0);
	change_mode_to(COMMANDMODE);
	int commandmodecutted=0;
	ppsettings = initial_settings;
	ppsettings.c_lflag &= ~ECHO;	
	ppsettings.c_lflag &= ~ICANON;
		
	tcsetattr(0,TCSANOW,&ppsettings);
	gotoxy(height+6,1);
	cout<<"> ";
	int flag_to_normal_mode=0;
	char ch;
	while(1){
		
		string queryfake="";
		int p=0;	
		char ch;
		int where=0;
		int pos=0;
		int px;
		while(1){
		
			ch = getchar();

			px = (int)ch;

			if(display_commands.size()>0){
				pos=2;
			}
			if(px==27){
		
				ppsettings = initial_settings;
				ppsettings.c_lflag &= ~ECHO;
				ppsettings.c_lflag &= ~ICANON;
				ppsettings.c_cc[VMIN]=0;
				ppsettings.c_cc[VTIME]=1;
		
				tcsetattr(0,TCSANOW,&ppsettings);
				int ccc = getchar();
				if(ccc==-1){

					ppsettings = initial_settings;
					ppsettings.c_lflag &= ~ECHO;
					ppsettings.c_lflag &= ~ICANON;
	
		
					tcsetattr(0,TCSANOW,&ppsettings);	
					y=1;
					scroll_k=0;
				
					commandmodecutted=1;
					print_command_mode_Scroll(0);
					queryfake = queryfake.substr(0,p);
					cout<<queryfake.substr(0,p);

					break;
				}
				else{

					ppsettings = initial_settings;
					ppsettings.c_lflag &= ~ECHO;
					ppsettings.c_lflag &= ~ICANON;
	
				
					tcsetattr(0,TCSANOW,&ppsettings);
					int charnew = (int)getchar();
					if(charnew==67){
						if(where<p){where++;
							gotoxy(height+6+pos,where+3);
						}
					}
					else if(charnew==68){
					
						if(where>0){
							where--;
							gotoxy(height+6+pos,where+3);
						}
					}
	//get remainde escape value
				}
			}
			else if(px==10){//enter
				queryfake = queryfake.substr(0,p);
				break;
			}else if(px==127){//backspace
				if(p>0){		
					if(where>0){			
						queryfake.erase(where-1,1);
						where--;
					}
				else{
					queryfake.erase(where,1);
				  }
  				p--;		
			
			}
			print_command_mode_Scroll(0);
			cout<<queryfake.substr(0,p);
			gotoxy(height+6+pos,where+3);
				

		}
		else {
		
			queryfake+=" ";
			queryfake.insert(where,1,ch);		

			p++;
			where++;
			print_command_mode_Scroll(0);
			cout<<queryfake.substr(0,p);
			gotoxy(height+6+pos,where+3);
	
		}

	}
	string query=queryfake;

	//getline (cin,query);
	
	query = rtrim(query);
	if(px!=27){
		display_commands.push_back(query);
		int size = split( query, v, ' ' );
	
		if(size==0){v.push_back("noop");}

		if(v[0].compare("clear")==0){//not clear	
	
		gotoxy(height+6,1);
		for(int i = 0;i<=command_mode_height+2;i++){
			gotoxy(height+6+i,1);
			for(int j=1;j<80;j++){
				cout<<" ";
			}
		}
		display_commands.clear();
		
		 scroll_command_position=0;
		gotoxy(height+6,1);
		cout<<"> ";
	}
  
	

	else if(v[0].compare("copy")==0){
		int flag=1,f_i;
		if(size>=3){
				
				int flagnahi = 0;
					

				string des;
					for(f_i =1;f_i<size-1;f_i++){

						if(flagnahi==1){break;}							
						
												
						string src;

						if(v[f_i][0]=='~'){src = home+"/"+v[f_i].substr(2);}else{
						src = path+"/"+v[f_i];}
						string filename;

						int z=v[f_i].size();
						int j= z-1;while(v[f_i][j]!='/' && j>=0){j--;} filename =v[f_i].substr(j+1,z); 


						struct stat fileStat;
	    				
	    					if(stat(src.c_str(),&fileStat) < 0)    
	   					{     
	    						return;
	    					}

				
												
							
						if(!S_ISDIR(fileStat.st_mode)){

							if(v[size-1][0]=='~'){
								 des = home+"/"+v[size-1].substr(2)+"/"+filename; 
							}
							else{ 
								des = path+"/"+v[size-1]+"/"+filename;}	
								copy_file(src,des);	
								struct stat perm;
								stat(src.c_str(),&perm);
								chown(des.c_str(),perm.st_uid,perm.st_gid);
								chmod(des.c_str(),perm.st_mode);
						}
						else{

				
							if(v[size-1][0]=='~'){
								 des = home+"/"+v[size-1].substr(2);  
							}
							else{ 	
								 des = path+"/"+v[size-1]; 
							}
						
							copy_directory(src,des,filename);
						}
						suc = "copied successfully";	
					}
							
					
					display_commands.push_back(suc);
					
				
			
		}
		else{
			
			
			suc = "Minimum two arguments required for this command";
			display_commands.push_back(suc);
		}
		print_command_mode_Scroll(1);
}
else if(v[0].compare("copy_file")==0){
		
		int flag=1,f_i;
		if(size>=3){
				
				int flagnahi = 0;
					

				string des;
					for(f_i =1;f_i<size-1;f_i++){

						if(flagnahi==1){break;}							
						
												
						string src;

						if(v[f_i][0]=='~'){src = home+"/"+v[f_i].substr(2);}else{
							src = path+"/"+v[f_i];}
							string filename;

							int z=v[f_i].size();
							int j= z-1;while(v[f_i][j]!='/' && j>=0){j--;} filename =v[f_i].substr(j+1,z); 
							if(v[size-1][0]=='~'){ 
								des = home+"/"+v[size-1].substr(2)+"/"+filename; 
							}
							else{ 
								des = path+"/"+v[size-1]+"/"+filename;}							
							
				
							copy_file(src,des);	
							struct stat perm;
							stat(src.c_str(),&perm);
							chown(des.c_str(),perm.st_uid,perm.st_gid);
							chmod(des.c_str(),perm.st_mode);
							suc = "copied successfully";	
						}
							
					
					display_commands.push_back(suc);
					
				
			
		}
		else{
			
			
			suc = "Minimum two arguments required for this command";
			display_commands.push_back(suc);
		}
		print_command_mode_Scroll(1);
	}
else if(v[0].compare("copy_dir")==0){
		
		int flag=1,f_i;
		if(size>=3){
				
				
					
					for(f_i =1;f_i<size-1;f_i++){
						string des,src;
						if(v[f_i][0]=='~'){
							src = home+"/"+v[f_i].substr(2);
						}
						else{
							src = path+"/"+v[f_i];}
							string filename;

							int z=v[f_i].size();
							int j= z-1;while(v[f_i][j]!='/' && j>=0){j--;} filename =v[f_i].substr(j+1,z); 
							
							if(v[size-1][0]=='~'){ 
								des = home+"/"+v[size-1].substr(2);  
							}
							else{
							 	 des = path+"/"+v[size-1]; 
							}
						
							copy_directory(src,des,filename);
						
					}
							
					suc = "copied successfully";
					display_commands.push_back(suc);
					
				
			
		}
		else{
			
			
			suc = "Minimum two arguments required for this command";
			display_commands.push_back(suc);
		}
		print_command_mode_Scroll(1);
	}
else if(v[0].compare("move")==0)
{

		int flag=1,f_i;
		if(size>=3){
				
				
					string des;
					for(f_i =1;f_i<size-1;f_i++){
												
						string src;

						if(v[f_i][0]=='~'){
							src = home+"/"+v[f_i].substr(2);
						}
						else{
							src = path+"/"+v[f_i];}
							string filename;
							int z=v[f_i].size();
							int j= z-1;while(v[f_i][j]!='/' && j>=0){j--;} filename =v[f_i].substr(j+1,z); 
					struct stat fileStat;
	    				
	    				if(stat(src.c_str(),&fileStat) < 0)    
	   				{     
	    					return;
	    				}
					if(!S_ISDIR(fileStat.st_mode)){		

						if(v[size-1][0]=='~'){ des = home+"/"+v[size-1].substr(2)+"/"+filename; }
							else{ des = path+"/"+v[size-1]+"/"+filename;}

												
						copy_file(src,des);
						struct stat perm;
						stat(src.c_str(),&perm);
						chown(des.c_str(),perm.st_uid,perm.st_gid);
						chmod(des.c_str(),perm.st_mode);
						remove(src.c_str());
						suc = "Moved successfully";print_dirs(0,height);
						}
						else{
		
							if(v[size-1][0]=='~'){ des = home+"/"+v[size-1].substr(2);  }else{ 	 des = path+"/"+v[size-1]; }
							
							copy_directory(src,des,filename);
							suc = "Moved successfully";
							removeDirectory(src);
							remove(src.c_str());print_dirs(0,height);
		
						}	
						
					}
							
					
					display_commands.push_back(suc);
					
				
			
		}
		else{
			
			
			suc = "Minimum two arguments required for this command";
			display_commands.push_back(suc);
		}
		print_command_mode_Scroll(1);

}
	else if(v[0].compare("move_file")==0){

		
		int flag=1,f_i;
		if(size>=3){
				
				
					string des;
					for(f_i =1;f_i<size-1;f_i++){
												
						string src;

						if(v[f_i][0]=='~'){
							src = home+"/"+v[f_i].substr(2);
						}
						else{
							src = path+"/"+v[f_i];}
							string filename;

							int z=v[f_i].size();
							int j= z-1;while(v[f_i][j]!='/' && j>=0){j--;} filename =v[f_i].substr(j+1,z); 
						

							if(v[size-1][0]=='~'){ des = home+"/"+v[size-1].substr(2)+"/"+filename; }
							else{ des = path+"/"+v[size-1]+"/"+filename;}

												
							copy_file(src,des);
							struct stat perm;
							stat(src.c_str(),&perm);
							chown(des.c_str(),perm.st_uid,perm.st_gid);
							chmod(des.c_str(),perm.st_mode);
							remove(src.c_str());
							suc = "Moved successfully";print_dirs(0,height);	
						
					}
							
					
					display_commands.push_back(suc);
					
				
			
		}
		else{
			
			
			suc = "Minimum two arguments required for this command";
			display_commands.push_back(suc);
		}
		print_command_mode_Scroll(1);


	}else if(v[0].compare("move_dir")==0){

		
		int flag=1,f_i;
		if(size>=3){
				
					
					for(f_i =1;f_i<size-1;f_i++){
						
						string des,src;
						if(v[f_i][0]=='~'){
							src = home+"/"+v[f_i].substr(2);
						}
						else{
							src = path+"/"+v[f_i];}
							string filename;

							int z=v[f_i].size();
							int j= z-1;while(v[f_i][j]!='/' && j>=0){j--;} filename =v[f_i].substr(j+1,z); 
							if(v[size-1][0]=='~'){ 
								des = home+"/"+v[size-1].substr(2);  
							}
							else{
								des = path+"/"+v[size-1]; 
							}
							
							copy_directory(src,des,filename);
							suc = "Moved successfully";
							removeDirectory(src);
							remove(src.c_str());print_dirs(0,height);
						
					}
							
					
					display_commands.push_back(suc);
					
				
			
		}
		else{
			
			
			suc = "Minimum two arguments required for this command";
			display_commands.push_back(suc);
		}
		print_command_mode_Scroll(1);


	}
	else if(v[0].compare("danish")==0 || v[0].compare("developer")==0){
		string about = "Developer : Danish MUkhtar\tRoll No : 2018201016\tBranch : M.Tech CSE";
		display_commands.push_back(about);
		print_command_mode_Scroll(1);
	}




	else if(v[0].compare("rename")==0){
		int flag=1,f_i;
		if(size==3){
				
				string src;
				
				for(f_i =1;f_i<size-1;f_i++){
						
					if(v[f_i][0]=='~'){
						src = home+"/"+v[f_i].substr(2);
					}else{
						src = path+"/"+v[f_i];}
						
						int z=src.size();
						int j= z-1;
						while(src[j]!='/' && j>=0){
							j--;
						}  						

						string des = src.substr(0,j+1)+v[size-1];						
						int ret = rename(src.c_str(),des.c_str());
							
						//copy_file(src,des);
			/*	struct stat perm;
			stat(src.c_str(),&perm);
			chown(des.c_str(),perm.st_uid,perm.st_gid);
			chmod(des.c_str(),perm.st_mode);
							remove(src.c_str());	
				*/	
						
					}
							
					suc = "Renamed Successfully";
					display_commands.push_back(suc);
				
				print_command_mode_Scroll(1);
			
			
		}
		else{
			
			
			suc = "Syntax Not Valid  : write 'rename fromFileName toFileName";
			display_commands.push_back(suc);
		}
		print_command_mode_Scroll(1);
	}



	else if(v[0].compare("create_file")==0){
		if(v.size()<3){
				
				suc = " ......Syntax Not Valid  : write 'create_file filename destination'";
		
				display_commands.push_back(suc);
			}else{
				
					
					for(int f_i =1;f_i<size-1;f_i++)
					{					
						if(v[size-1][0]=='~'){
					
							suc=home+"/"+v[size-1].substr(2)+"/"+v[f_i];	
					
						}else{
							suc = path+"/"+v[size-1]+"/"+v[f_i];
						}
						create_file(suc);
					}
					suc = "Created file / files successfully";
					display_commands.push_back(suc);
				
			}
		print_command_mode_Scroll(1);
		}
	else if(v[0].compare("create_dir")==0){
		if(v.size()<3){
				suc = "Syntax Not Valid  : write 'create_dir filename destination'";
				display_commands.push_back(suc);
			}else{
				

					
					for(int f_i =1;f_i<size-1;f_i++)
	
					{	
								
				if(v[size-1][0]=='~'){
					
					suc=home+"/"+v[size-1].substr(2)+"/"+v[f_i];	
					
				}
				else{
					suc = path+"/"+v[size-1]+"/"+v[f_i];
				}						
				create_directory(suc);
						
		
					}

		
				display_commands.push_back(suc);
			}
		print_command_mode_Scroll(1);
		
	}
	else if(v[0].compare("delete_file")==0){
		if(v.size()<2 || v.size()>2){
				suc = "Syntax Not Valid  : write 'delete_file destination'";
				display_commands.push_back(suc);
			}
		else{
				string destination;				
				if(v[1][0]=='/'){
					destination=home+"/"+ v[1].substr(1);	
					}else if(v[1][0]=='~'){
					  destination=home+"/"+ v[1].substr(2);				
					
					}else{
					destination = path +"/"+ v[1];
					}
				 // path + v[1].substr(1);
				//rename(destination.c_str(),("./trash_folder_2018201016/"+v[1]).c_str());
				//trash_records[v[1]] = destination; 
				remove(destination.c_str());
				suc = "Deleted "+v[1] +" Sucessfully";
				display_commands.push_back(suc);
				print_dirs(0,height);
				}
		print_command_mode_Scroll(1);
		}
		else if(v[0].compare("delete_dir")==0){
		if(v.size()<2 || v.size()>2){
				suc = "Syntax Not Valid  : write 'delete_dir destination'";
				display_commands.push_back(suc);
		}
		else{
				
			string destination;				
			if(v[1][0]=='/'){
			destination=home+"/"+ v[1].substr(1);	
			}
			else if(v[1][0]=='~'){
				destination=home+"/"+ v[1].substr(2);				
					
			}
			else{
				destination = path +"/"+ v[1];
			}
			removeDirectory(destination.c_str());
			remove(destination.c_str());
			suc = "Deleted "+v[1] +" Sucessfully";
			display_commands.push_back(suc);
			print_dirs(0,height);
				}
			print_command_mode_Scroll(1);
		}
	else if(v[0].compare("goto")==0)
		{
		if(v.size()<2 || v.size()>2){
				suc = "Syntax Not Valid  : write 'goto destination'";
				display_commands.push_back(suc);
		}
		else{
				while(back!=0){
				forward_history.pop();
				fkh.pop();
					back--;
				}
				back=0;
				
				back_history.push(path);
				bkh.push(pathdup);
				if(v[1].compare("/")==0){
					path=home;	
					pathdup = home; 
				}
				else if(v[1][0]=='~'){
					path=home+"/"+ v[1].substr(2);				
					pathdup = home+"/"+ v[1].substr(2);			
				}
				else{
					path = path +"/"+ v[1];
					pathdup=pathdup +"/"+ v[1];
				}
				
				suc = path;
				display_commands.push_back(suc);
				real_clean();				
				fflush(stdout);		
				
				print_dirs(0,height);
				y=1;
				scroll_k=0;
				
		}
		print_command_mode_Scroll(1);
		}
else if(v[0].compare("search")==0)
		{
		if(v.size()<2 || v.size()>2){
				suc = "Syntax Not Valid  : write 'search filename'";
				display_commands.push_back(suc);
		}
		else{
				search_path.clear();
				int searched = searchfile(path,v[1]);
				if(search_path.size()==0){
				suc = "Not Found";

				display_commands.push_back(suc);
				}else{
				while(back!=0){
				forward_history.pop();
				fkh.pop();
					back--;
				}
				back=0;
				
				
				
				real_clean();				
				fflush(stdout);		
				
				y=1;
				scroll_k=0;commandmodecutted=1;

				suc = "Command executed succesfully";
				display_commands.push_back(suc);
			
				searchConsole(0,height,v[1]);

				}


		}
		print_command_mode_Scroll(1);
		}
	else if(v[0].compare("help")==0){
		if(v.size()==1){
			suc ="Few commands : 1.copy 2.move  3.rename  and more";
		
			display_commands.push_back(suc);
	
			print_command_mode_Scroll(1);
	
		}else{
			suc ="'help' command needs no argument";
		
			display_commands.push_back(suc);
	
			print_command_mode_Scroll(1);
			}
		}





else if(v[0].compare("snapshot")==0){
		string pathre = path;
		if(v.size()==3){
			pathre = pathre+"/"+v[1];
			if((char)v[1][0]=='~'|| (char)v[1][0]=='/' ){
		//	suc ="'~', '.', '/' ON START :PATH SHOULD BE FROM CURRENT DIR.";
			v[1] = v[1].substr(2);
		//	display_commands.push_back(suc);
		//	print_command_mode_Scroll(1);
			pathre = home+v[1].substr(2);
			}
				
			//else{			
			out.open(v[2]);
	    		snap_shot(pathre,"."+v[1]);
	
	    		out.close();			
			suc="saved at ./"+v[2];		
			display_commands.push_back(suc);
			
			print_command_mode_Scroll(1);
			//}
		}else{
			suc ="'snapshot'needs two arguments only";
		
			display_commands.push_back(suc);
	
			print_command_mode_Scroll(1);
			}
		}

	
		else {
		
		suc ="Command Not Found , type 'help' to find commands";
		
		display_commands.push_back(suc);
	
		print_command_mode_Scroll(1);
		}

	}

			if(commandmodecutted){

				gotoxy(height+8,1);
				for(int i = 0;i<command_mode_height;i++){
		
					for(int j=1;j<80;j++){
						cout<<" ";
					}
				}
				display_commands.clear();
		
				 scroll_command_position=0;
				gotoxy(height+8,1);
				cout<<"> ";


				new_settings = initial_settings;

				new_settings.c_lflag &= ~ECHO;

				new_settings.c_lflag &= ~ICANON;
				change_mode_to(NORMALMODE);

				if(tcsetattr(0, TCSANOW, &new_settings) != 0) {
					fprintf(stderr,"could not set attributes\n");
				}


				gotoxy(start_x,start_y);
				break;
			}
		}
	
}
void real_clean(){

	for(int i=0;i<height+3;i++){ 
		gotoxy(i+start_x,1);
		for(int j = 1;j<80;j++){
			cout<<" ";
		}

	}
	gotoxy(start_x,start_y);
}
void print_dirs(int j,int limit_y){



	n=scandir(path.c_str(),&namelist,NULL,alphasort);

	real_clean();
	change_mode_to(mode_num);
	nn=n;
	n--;
	init_Screen();
		pathshow();
	gotoxy(start_x,start_y);

	int numbers=j+1;
	int ini=j;
	if(nn<limit_y){
		limit_y=nn;
	}
	gotoxy(start_x,start_y);


	while(ini<limit_y){

	
	printf(" %d ",numbers);
	if((int)namelist[ini]->d_type==4){
		printf("\x1B[36m");
	}
	string cc = namelist[ini]->d_name;
	if(cc.size()>25){
		cc=cc.substr(0,22);
		printf("%s...",cc.c_str());
	}
	else{

		printf("%s",namelist[ini]->d_name);

	}	
	if((int)namelist[ini]->d_type==4){
		printf("\x1B[0m");

	}



	 struct stat fileStat;
	 string pp = path+"/"+namelist[ini]->d_name;
	 if(stat(pp.c_str(),&fileStat) < 0)    
	 {     
	    	return;
	 }


	 printf("\033[%d;28H",ini-j+3);
	
	 float sizedata =(int)fileStat.st_size;
	 if((sizedata/1024)>=1){
		sizedata = (sizedata/1024);
			     if((sizedata/1024)>=1){
					sizedata = (sizedata/1024);
						
			     if((sizedata/1024)>=1){
					sizedata = (sizedata/1024);
					 printf(" %.1fGB",sizedata);
					
			    }else{
				    printf(" %.0fMB",sizedata);
				}		
					
			    }else{
				    printf(" %.0fKB",sizedata);
				}		
		}else{
			    printf(" %.0fB",sizedata);

	}
	
	    printf("\033[%d;%dH", ini-j+3,36 ); 
		
		string permissions="";
		if(S_ISDIR(fileStat.st_mode)){
			permissions="d";
		}else{
			permissions="-";
			
		}
	
		
		if(fileStat.st_mode & 256){
			permissions+="r";
		}else{
			permissions+="-";
		}
		if(fileStat.st_mode & 128){
			permissions+="w";
		}else{
			permissions+="-";
		}
		if(fileStat.st_mode & 64){
			permissions+="x";
		}else{
			permissions+="-";
		}
		if(fileStat.st_mode & 32){
			permissions+="r";
		}else{
			permissions+="-";
		}
		if(fileStat.st_mode & 16){
			permissions+="w";
		}else{
			permissions+="-";
		}
		if(fileStat.st_mode & 8){
			permissions+="x";
		}else{
			permissions+="-";
		}   
		if(fileStat.st_mode & 4){
			permissions+="r";
		}else{
			permissions+="-";
		}
		if(fileStat.st_mode & 2){
			permissions+="w";
		}else{
			permissions+="-";
		}
		if(fileStat.st_mode & 1){
			permissions+="x";
		}else{
			permissions+="-";
		} 
		cout<<permissions;

	   	 struct passwd *pw = getpwuid(fileStat.st_uid);
	    	struct group  *gr = getgrgid(fileStat.st_gid);
	    

	   	 printf("\033[%d;%dH", ini-j+3,50);  
	   	 printf("%s %s",gr->gr_name,pw->pw_name);
	    
		printf("\033[%d;%dH", ini-j+3,65 );  
		string ss = ctime(&fileStat.st_mtime);

	    	cout<<" "<<ss.substr(4,12); 

		cout<<"\n";

	   
	    	numbers++;
	    	ini++;
		
	}
	gotoxy(start_x,start_y);
}

int main(int arg,char *args[])
	{

//mkdir("trash_folder_2018201016", S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);

	if(arg==1){
		path=".";
		home=path;
		pathdup=path;

	}
	else{

		path=args[1];

		pathdup=path;
	}
	
	signal(SIGINT, INThandler);
	
	
	int a;
	
	real_clean();
	//system("reset");	
	printf("\033[2J\033[1;1H");
	fflush(stdout);
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	
	tcgetattr(0,&initial_settings);
	new_settings = initial_settings;

	new_settings.c_lflag &= ~ECHO;

	new_settings.c_lflag &= ~ICANON;

	if(tcsetattr(0, TCSANOW, &new_settings) != 0) {
	fprintf(stderr,"could not set attributes\n");
	}




	
	print_dirs(0,height);
	gotoxy(start_x,start_y); // y,1
	char ch;
	int flag=0;

	while(1){
	ch = getchar();
	int s = (int)ch;
	


	switch(s){

		case 58:{
				CommandMode();	
				print_dirs(0,height);
				
				new_settings.c_lflag &= ~ECHO;

				new_settings.c_lflag &= ~ICANON;

				if(tcsetattr(0, TCSANOW, &new_settings) != 0) {
				fprintf(stderr,"could not set attributes\n");
				}
				y=1;
				scroll_k=0;
				gotoxy(y+start_x-1,1);
				
				break;		
			}

		case 127:{
					
				if(pathdup.compare(home)==0){break;}
					while(back!=0)
					{
					forward_history.pop();
					fkh.pop();
						back--;
					}
					back=0;
					
					back_history.push(path);
					bkh.push(pathdup);pathdup = getactualpath(pathdup);
					path = path +"/"+namelist[1]->d_name;
					real_clean();
					fflush(stdout);		
					
					print_dirs(0,height);
					
					new_settings.c_lflag &= ~ECHO;

					new_settings.c_lflag &= ~ICANON;

					if(tcsetattr(0, TCSANOW, &new_settings) != 0) {
					fprintf(stderr,"could not set attributes\n");
					}
					y=1;
					scroll_k=0;
					gotoxy(start_x,start_y);//y,1	
			break;}
			
		case 65:
			{
					
				if(y>=2){
					y--;
					gotoxy(y+start_x-1,1);
						
						break;
				}
				
				if(scroll_k!=0)
				{
	
				gotoxy(start_x,start_y);
				scroll_k=scroll_k-1;
				print_dirs(scroll_k,height+scroll_k);
				gotoxy(start_x,start_y);
				
				}
				else
				{
								
				}
				break;			
			}
			
		case 66:{	

				if(nn>height){
				if(height-(height-y)+scroll_k<nn){
				if(y<height){
					y++;
					gotoxy(y+start_x-1,1); 
					break;
				}		
				gotoxy(start_x,start_y);
				scroll_k++;
				print_dirs(scroll_k,height+scroll_k);
				gotoxy(height+start_x-1,1);
				}
				}else{
				if(y<nn)
				{
					y++;
					gotoxy(y+start_x-1,1);
				}	

				}
				break;			
			}
			//quit (q)
		case 113:{
				flag=1;
				break;
			}
			//enter 
		case 10:{	

				if((y+scroll_k-1)==0)
				{
					break;
				}
				if((y+scroll_k-1)==1 && pathdup.compare(home)==0){//back_history.size()==0
					break;
				}
				
				while(back!=0){
				forward_history.pop();
				fkh.pop();
					back--;
				}
				back=0;
				if((int)namelist[y+scroll_k-1]->d_type==4){
				if((y+scroll_k-1)==1){//back_history.size()==0
					bkh.push(pathdup);
					pathdup = getactualpath(pathdup);				
				
				}else{
						bkh.push(pathdup);
					pathdup = pathdup +"/"+namelist[y+scroll_k-1]->d_name;
					}
				
				back_history.push(path);
				path = path +"/"+namelist[y+scroll_k-1]->d_name;
				//printf("\033[2J\033[1;1H");
				real_clean();				
				fflush(stdout);		
				
				print_dirs(0,height);
				//cout<<"----"<<y+scroll_k-1<<"---";
				new_settings.c_lflag &= ~ECHO;

				new_settings.c_lflag &= ~ICANON;

				if(tcsetattr(0, TCSANOW, &new_settings) != 0) {
					fprintf(stderr,"could not set attributes\n");
				}
					y=1;
					scroll_k=0;
					gotoxy(y+start_x-1,1); // y,1//......y+2

				}
				else{
					string pathre = path;
					for(int k=0;k<path.size();k++){
						if(pathre[k]==' '){
	
							pathre.insert(k,1,'\\');
							k+=1;
					}
				}
				string path1 = pathre +"/"+namelist[y+scroll_k-1]->d_name;
				pid_t pid = fork();
				if (pid == 0) {

					int out = open("err.log", O_RDWR|O_CREAT|O_APPEND, 0600);
					if (-1 == out) { perror("opening cout.log"); return 255; }
    					int save_out = dup(fileno(stderr));
   					if (-1 == dup2(out, fileno(stderr))) { perror("cannot redirect stdout"); return 255; }
      					
    			  				
				execl("/usr/bin/xdg-open", "xdg-open", path1.c_str(), (char *)0);
						
    					fflush(stderr); close(out);
  
    					dup2(save_out, fileno(stderr));
   
	
    					close(save_out);
  				
  					exit(1);
				}
				
					}

			break;
			}
			//left-arrow <-
			case 68:{	
				if(back_history.size()==0){
					
					break;
				}
				back++;
				forward_history.push(path);
				
				fkh.push(pathdup);
				path = back_history.top(); pathdup = bkh.top();bkh.pop();
				back_history.pop();
				//printf("\033[2J\033[1;1H");
				real_clean();				
				fflush(stdout);		
				
				print_dirs(0,height);
				
				new_settings.c_lflag &= ~ECHO;

				new_settings.c_lflag &= ~ICANON;

				if(tcsetattr(0, TCSANOW, &new_settings) != 0) {
				fprintf(stderr,"could not set attributes\n");
				}
				y=1;
				scroll_k=0;
				gotoxy(y+start_x-1,1); // y,1//.......y+2
				

			break;
			}
			//right_arrow ->
			case 67:{	
				if(forward_history.size()==0){
					break;
				}
				back--;
				back_history.push(path); bkh.push(pathdup);
				path = forward_history.top();
				pathdup = fkh.top();
				fkh.pop();
				forward_history.pop();
				real_clean();
				
				fflush(stdout);		
				
				print_dirs(0,height);
				
				new_settings.c_lflag &= ~ECHO;

				new_settings.c_lflag &= ~ICANON;

				if(tcsetattr(0, TCSANOW, &new_settings) != 0) {
				fprintf(stderr,"could not set attributes\n");
				}
				y=1;
				scroll_k=0;
				gotoxy(y+start_x-1,1);//y,1/.......y+2
				

			break;
			}
			//home 'h'
			case 104:{
					while(back!=0)
					{
					forward_history.pop();
					fkh.pop();
						back--;
					}
					back=0;
					
					back_history.push(path); bkh.push(pathdup);
					path = home; pathdup = home;
					real_clean();
					cout<<"home acalled";
					//printf("\033[2J\033[1;1H");
					fflush(stdout);		
					
					print_dirs(0,height);
					
					new_settings.c_lflag &= ~ECHO;

					new_settings.c_lflag &= ~ICANON;

					if(tcsetattr(0, TCSANOW, &new_settings) != 0) {
					fprintf(stderr,"could not set attributes\n");
					}
					y=1;
					scroll_k=0;
					gotoxy(y+start_x-1,1);//y,1////.........y+2

					

				
				break;
				}

		}
		if(flag==1){
			break;
		}

	}
	tcsetattr(0,TCSANOW,&initial_settings);
	printf("\033[2J\033[1;1H");
	real_clean();
	return 0;
}
