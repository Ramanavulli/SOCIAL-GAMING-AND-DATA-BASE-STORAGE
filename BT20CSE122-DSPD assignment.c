#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define file_size 100
typedef struct player_information
{
	char player_id[10];//(primary key)
	char name[50];
	struct registration_date
	{
		int dd;
		int mm;
		int yyyy;
	}registration_date;
	char game_id[30];
	int no_of_players;
	int gamesplayed;
	int gameswon;
	int scores;
	int prizes;
	char game_preferences[50];
}player_information;
typedef struct game_master_details
{
	char game_id[10];//(primary key)
	char name[50];
	char type[20]; //(single/multiple user)
	int no_of_players;
}game_master_details;
typedef struct games_played_details
{
	char game_id[20];//(primary key)
	char player_id[10];
	int score;
	int awards;
	int active_days;
	int ply_count;
	struct date_of_game_start
	{
		int ddstart;
		int mmstart;
		int yyyystart;
	};
	struct date_of_game_end
	{
		int ddend;
		int mmend;
		int yyyyend;	
	};
}games_played_details;
typedef struct Guest_user_details
{
	char id[20];  //(primary key)
	char name[50];
	char date[20];
}Guest_user_details;


void intialize_player_information(struct player_information pi[file_size])
{
	int i;
	for (i=0;i<file_size;i++)
	{
		pi[i].player_id[10]='\0';
		pi[i].name[50]='\0';
		pi[i].registration_date.dd=0;
		pi[i].registration_date.mm=0;
		pi[i].registration_date.yyyy=0;
		pi[i].no_of_players=0;
		pi[i].game_preferences[50]='\0';
		pi[i].gamesplayed =0;
		pi[i].gameswon =0;
		pi[i].scores =0;
		pi[i].prizes=0;
	}
}
//initialization
void intialize_game_master_details(struct game_master_details gmd[file_size])
{
	int k;
	for (k=0;k<file_size;k++)
	{
		gmd[k].game_id[10]='\0';
		gmd[k].name[50]='\0';
		gmd[k].type[20]='\0';
		gmd[k].no_of_players=0;
		
	}
	
}
void intialize_games_played_details(struct games_played_details gpd[file_size])
{
	int l;
	for (l=0;l<file_size;l++)
	{
		gpd[l].game_id[20]='\0';
		gpd[l].player_id[10]='\0';
		gpd[l].score=0;
		gpd[l].awards=0;
		gpd[l].active_days=0;
		gpd[l].ddstart=0;
		gpd[l].mmstart=0;
		gpd[l].yyyystart=0;
		gpd[l].ddend=0;
		gpd[l].mmend=0;
		gpd[l].yyyyend=0;
		
	}
	
}
void intialize_Guest_user_details(struct Guest_user_details gud[file_size])
{
	int m;
	for (m=0;m<file_size;m++)
	{
		gud[m].id[20]='\0';
		gud[m].name[50]='\0';
		gud[m].date[20]='\0';
		
	}
}
// adding a new user
void add_newuser( struct player_information pi[file_size],int N)
{
	int i,n;
 	printf("\n enter the number of new players :");
 	scanf("%d",&n);
 	
	for(i=0;i<n;i++)
    {
    	printf("\n enetr the player ID:");
 	    scanf("%s",&pi[i+N].player_id);
 	
 	    printf("\n enetr the name:");
 	    scanf("%s",&pi[i+N].name);
 	    
 	    printf("\n enetr the registration date:");
 	    scanf("%d %d %d",&pi[i+N].registration_date.dd,&pi[i+N].registration_date.mm,&pi[i+N].registration_date.yyyy);
 	    
 	    printf("\n enetr the no.of games played:");
 	    scanf("%d",&pi[i+N].gamesplayed);
 	    
 	    printf("\n enetr the no.of games won:");
 	    scanf("%d",&pi[i+N].gameswon);
 	    
 	    printf("\n enetr the score:");
 	    scanf("%d",&pi[i+N].scores);
 	    
 	    printf("\n enetr the prizes:");
 	    scanf("%d",&pi[i+N].prizes);
 	    
 	    printf("\n enetr the game preferences:");
 	    scanf("%s",&pi[i+N].game_preferences);
 	    
	}
	N=N+n;

//updated data
	
	printf("the updater data is:");
	for(i=0;i<N;i++)
	{
		printf("\n %s %d %d %s %s ",pi[i+N].player_id,pi[i+N].name,pi[i+N].registration_date.dd,pi[i+N].registration_date.mm,pi[i+N].gamesplayed );
		print("\n The new user was added sucessfully");
	}	
}
//search_active_user
void search_active_user(struct player_information pi[],int count,int k)
{
	int i;
	printf("Active users :-\n");
    for( i=0;i<count;i++)
	{
        if(pi[i].gamesplayed>k)
		{
            printf("ID: P%d\t%s\n",pi[i].player_id,pi[i].name);
        }
    }

}
//search_inactive_user
void search_inactive_user(struct player_information pi[],int player_count,struct games_played_details gpd[],int game_count)
{
	int inactive_user[100];
    int i,j,k,l,days;
    int inactive_count=-1;

    for( i=0;i<game_count;i++)
	{

        for( j=0;j<gpd[i].ply_count;j++)
		{
            int d= abs((gpd[j].ddstart)-(gpd[j].ddend));
			int m= abs((gpd[j].mmstart)-(gpd[j].mmend));
			int y= abs((gpd[j].yyyystart)-(gpd[j].yyyyend));
			days=d+30*m+365*y;
             for( k=0;k<pi[i].no_of_players;k++)
			 {
                 if(games_played_details.active_days<days )
				 {
                     //check if usr is alredy noted or not
                     if(inactive_count==-1)
                        inactive_user[++inactive_count]=gpd[i].player_id[k];
                    else{
                        int flag=1;
                        for( l=0;l<inactive_count&&flag;l++)
						{
                            if(gpd[i].player_id[k]==inactive_user[l])
                                flag=0;
                        }
                        if(flag==1)
                        inactive_user[++inactive_count]=gpd[i].player_id[k];
                    }

                 }
             }
        }
         printf("game_id: %d inactive user are :\n",i);
        for( i=0;i<inactive_count;i++)
		{
            printf(" %s\n",pi[inactive_user[i]].name);
        }
    }
  
}	
//Display_Details_G
void Display_Details_G(struct player_information pi[],int count,int game)
{
	int i;
    printf("\tplayers\tId\n");
    for( i=0;i<count;i++)
	{
        
        if(pi[i].game_id==game)
		{
        printf("Name: %s\tP%d\n",pi[i].name,pi[i],i);
                
        }
        

    }
}
//Sorting_mostprizes
void Sorting_mostprizes(struct game_master_details games[] ,int count,struct games_played_details play[],int play_counter)
{
	int n;
	int i, j, max, id = 0;
	printf("Enter n:");
	scanf("%d",&n);
    struct game_master;games[20];
	for(i=0;i<n;i++)
	{
		printf("Enter game master details:%d\n",i+1);
		printf("Enter id:");
		scanf("%d",&games[i].game_id);
		printf("Enter name:");
		scanf("%s",games[i].name);
		printf("Enter type:");
		scanf("%s",games[i].type);
		printf("Enter no.of players required:");
		scanf("%d",&games[i].no_of_players);
	}
	
	int gmaster[count];
	
	for(i=0; i<count; i++){
		gmaster[i] = 0;
		for(j=0; j<play_counter; j++)
		{
			if(play[j].game_id == i){
				if(strcmp(play[j].awards, "none") != 0)
				{
					gmaster[i] ++; 
				}
			}
		}
	}
	max=gmaster[0];
	for(i=1; i<count; i++){
		if(max < gmaster[i])
		{
			max = gmaster[i];
			id = i;
		}
	}
	
	printf("Maximum prizes are in %s", games[id].name);
}
//bubbleSort
void bubbleSort(int a[][2], int n,int p)
{
    int i, j;
    int q=(n>p+1)?p+1:n;
    for (i = 0; i < q-1; i++)  
	{  
      for (j = 0; j < n-i-1; j++)
       { 
           if (a[j][0] > a[j+1][0])
            swap(&a[j][0], &a[j+1][0]);
       }
    }
}

//top_5games
void top_5games(struct games_played_details gpd[],int game_count)
{

       int d[50][2];
       int data[20][0];
       int i,j,days=0;
       for(i=0;i<game_count;i++)
	   {
           for(j=0;j<gpd[i].ply_count;j++)
		   {
               
                   int d= abs((gpd[j].ddstart)-(gpd[j].ddend));
				   int m= abs((gpd[j].mmstart)-(gpd[j].mmend));
				   int y= abs((gpd[j].yyyystart)-(gpd[j].yyyyend));
				   days+=d+30*m+365*y+1;
           }
           data[i][0]=days;
           data[i][1]=i;
       }
      bubbleSort(d,50,5);
      for( i=game_count-1;i>game_count-1-5;i--)
        printf("Game_id: %d  days: %d\n",data[i][1],data[i][0]);


}
//remove_guest
void remove_guest(struct games_played_details gpd[],struct Guest_user_details gud[])
{
	int d,m,y,total,a;
	char id[20];
	printf("enter guest user no in list:");
	scanf("%d",&a);
	
	d= abs((gpd[a].ddstart)-(gpd[a].ddend));
	m= abs((gpd[a].mmstart)-(gpd[a].mmend));
	y= abs((gpd[a].yyyystart)-(gpd[a].yyyyend));
	total=d+30*m+365*y;
	if(total>20)
	{
		gpd[m].player_id[20]='\0';
		gud[m].name[50]='\0';
		gud[m].date[20]='\0';
		
	}
	
}
int main()
{
	int ch,ch1,ch2;
    printf("\n 1.Add_user");
        printf("\n 2.Search");
        printf("\n 3.Sorting");
        printf("\n 4.Delete ");
        printf("\n 0.Exit");

        printf("\n Enter your choice :");
        scanf("%d",&ch);

        while (ch>0)
		{
          if(ch==1)
          {
            add_newuser();
		  }
          
          if(ch==2)
          {
          	printf("\n Enter your choice :");
             scanf("%d",&ch1);
             switch (ch1)
             {
             	case 1:
             		search_inactive_user();
             		break;
             	case 2:
             		search_active_user();
             		break;
			 }
          
		  }
           if(ch==3)
           {
           	printf("\n Enter your choice :");
             scanf("%d",&ch2);
             switch (ch2)
             {
             	case 1:
             		Sorting_mostprizes();
             		break;
             	case 2:
             		top_5games();
             	case 3:
             		Display_Details_G();
             		break;
			 }
          
		   }
          if(ch==4)
          {
          	remove_guest();
		  }
          
          if(ch==0)
          {
          	break;
		  }
        }
    }
        
    
    return 0;
}

