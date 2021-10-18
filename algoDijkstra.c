#include <stdio.h>
#include<stdlib.h>

typedef struct suiv{
int n;
int *suivant;
}suiv;


// on a utilisé une matrice graphe[ordre][ordre] a double dimension pour presenter le graphe
int** lireGraphe(int ordre,int nbr)
{
	int i,**graphe,som_initial,som_final;
    graphe=(int **)calloc(ordre,sizeof(*graphe));
	for(i=0;i<ordre;i++) graphe[i]=(int *)calloc(ordre,sizeof(**graphe));
	printf("Lecture des poids\n");
	for(i=0;i<nbr;i++)
	{
		printf("entrez le sommet intital\n");
		scanf("%d",&som_initial);
		printf("entrez le sommet final\n");
		scanf("%d",&som_final);
		printf("entrez le poid de l'arc %d-%d\n",som_initial,som_final);
		scanf("%d",&graphe[som_initial][som_final]);
	}
	return graphe;
}
void afficherGraphe(int** graphe,int ordre){

	int i,j;
	printf("Sommet initial\tSommet final\tpoid\n");
	for(i=0;i<ordre;i++)
	{
		for(j=0;j<ordre;j++)
	     {
		 if(graphe[i][j]!=0)
		{	printf("%d\t\t%d\t\t%d\t\t",i,j,graphe[i][j]);
			printf("\n");}
		else continue;
		}
	}
}
// La fonction Suivant() retourne une structure de type suiv qui contient le nombre de successeur d un sommet et un tableau de successeur
 suiv Suivant(int** graphe,int ordre,int s)
{
	int i=0,j,k;
	suiv sucs;
	sucs.n=0;
	sucs.suivant=(int*)malloc(ordre*sizeof(int*));
	for(j=0;j<ordre;j++)
		{
		if(graphe[s][j]==0) continue;
		else {
		sucs.suivant[sucs.n]=j;
		sucs.n=sucs.n+1;
		}
		}
		return sucs;
}
// la foncton Dijkstra retourne lun pointeur sur le tableau du Successeur marqués; 
 int* Dijkstra(int **graphe, int ordre )
 {
	int i,j,min,cmpt,pos;
	int **D;
	int *SommetMarq;
	// allocation du tableau de dijkstra
    D=(int**)malloc(ordre*sizeof(*D));
	for(i=0;i<ordre;i++)  D[i]=(int*)malloc(ordre*sizeof(**D));
	SommetMarq=(int*)malloc(ordre*sizeof(int));
	D[0][0]=0;
	SommetMarq[0]=0;     //stocket le premier sommet selectionné
	// la representation numerique de l'infini est -1
	//la representation numerique de sommets marqués est -2
	for(i=1;i<ordre;i++)
	{
		D[0][i]=-1;   // -1  pour tous  sommets\{Sommet selectionné}
		D[i][0]=-2;  //marquer les cases du sommet marqué
	}
     suiv Sc=Suivant(graphe,ordre,SommetMarq[0]); 
	 for(i=1;i<ordre;i++)
	 {      cmpt=0;
	 	for(j=0;j<Sc.n;j++)
	 	{	if(i==Sc.suivant[j])
	 		{	int pos=Sc.suivant[j];
	 			D[1][i]=graphe[0][pos];
	 			cmpt++;
			 }
		 }
		 if (cmpt==0) D[1][i]=-1;
	  } 
	 // recherche de le coefficient minimale  dans la ligne 1 du tableau D[ordre][ordre];
	min=D[1][1];
	pos=0;	
	for(i=1;i<ordre;i++){
		if(D[1][i]<=min && D[1][i]>0)
		{
			min=D[1][i];
			pos=i;
		}
	}
   SommetMarq[1]=pos; // stocket le deuxieme sommet marqué
   suiv	Sc1=Suivant(graphe,ordre,SommetMarq[1]);
    for(i=2;i<ordre;i++){
    	D[i][pos]=-2;  // marquer les cases du sommet  marqué
	}
	 for(i=1;i<ordre;i++){
	 	cmpt=0;
	 	if(i==SommetMarq[1]) continue;
	 	
	 	for(j=0;j<Sc1.n;j++)
	 	{	if(i==Sc1.suivant[j])
	 		{  D[2][i]=D[1][pos]+graphe[pos][i];
	 			cmpt++;}
	    }
		 if (cmpt==0) 
		 {	if(D[1][i]>-1)  D[2][i]=D[1][i];
			if(D[1][i]==-1) D[2][i]=-1; 	
		 }
	  } 
	 //  recherche de le coefficient minimale  dans la ligne 2 du tableau D[ordre][ordre]; 
	 min=D[2][1];
	 pos=0;	
	 for(i=1;i<ordre;i++){
		if(D[2][i]<=min && D[2][i]>0)
		{   min=D[2][i];
			pos=i;
		}
	}
	//k=2;
	SommetMarq[2]=pos;
	suiv Sc2=Suivant(graphe,ordre,SommetMarq[2]);
	  for(i=3;i<ordre;i++){
    	D[i][pos]=-2;
	} 
    for(i=3;i<ordre;i++)	
	  D[3][i]=D[2][i];
	//recherche de la coefficient minimale  dans la ligne 3 du tableau D[ordre][ordre];  
    min=D[3][3];
	pos=0;	
	for(i=3;i<ordre;i++){
		if(D[3][i]<=min && D[3][i]>0)
		{   min=D[3][i];
			pos=i;
		}
	}
	//k=3
	SommetMarq[3]=pos;  // stocker le 4 ieme sommet  marqué
	suiv Sc3=Suivant(graphe,ordre,SommetMarq[3]);
	 for(i=4;i<ordre;i++)
    	D[i][pos]==-2;	
	 for(i=4;i<ordre;i++) 
	 D[4][i]=D[3][pos]+graphe[pos][i];
	 //recherche de la coefficient minimale  dans la ligne 4 du tableau D[ordre][ordre];
	 min=D[4][4];
	 	for(i=4;i<ordre;i++){
		if(D[4][i]<=min )
		{   min=D[4][i];
			pos=i;
		}
	}
	//k=4
	SommetMarq[4]=pos; // stoker le 5 ieme sommet  marqué
	suiv Sc4=Suivant(graphe,ordre,SommetMarq[4]);
	D[5][pos]=-2;
	D[5][5]=D[4][pos]+graphe[pos][5];
	//k=5
	SommetMarq[5]=ordre-1; // le dernier sommet  marqué
    return SommetMarq;
 }
int main(int argc, char *argv[]) {
	int **g;
	int nbr,ordre,i;
	int *dijk;
	printf("entrez l'ordre du graphe\n");
	scanf("%d",&ordre);
    g=(int **)malloc(ordre*sizeof(*g));
	for(i=0;i<ordre;i++) g[i]=(int *)malloc(ordre*sizeof(**g));
	printf("entrez le nombre d'arcs\n");
	scanf("%d",&nbr);
	g=lireGraphe(ordre,nbr);
	afficherGraphe(g,ordre);
	dijk=(int *)malloc(ordre*sizeof(int));
	dijk=Dijkstra(g,ordre);
	printf("le chemin le plus court :\t");
	for(i=0;i<ordre-1;i++) printf("%d -> ",dijk[i]);
	printf("%d",dijk[ordre-1]);
	
	return 0;
}
