#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Ders {
    char d_ismi[50];
    char d_kodu[10];
    int d_puani;
};


struct Ogrenci {
    char isim[50];
    char soyisim[50];
    int ogrenci_id;
    struct Ders Dersler[10];
    int ders_sayisi;
};

struct Ogrenci* kodBulma(struct Ogrenci* Ogrenciler, int ogr_sayisi, char* arananKod) {
    for (int i = 0; i < (ogr_sayisi); i++)
        {
        for (int j = 0; j < Ogrenciler[i].ders_sayisi; j++)
                {
                if ( strcmp(Ogrenciler[i].Dersler[j].d_kodu, arananKod) == 0 )
                    {
                    return &Ogrenciler[i];
                    }
                }
        }
            return NULL;

}



struct Ogrenci* soyadBulma(struct Ogrenci* Ogrenciler, int ogr_sayisi, char* silinecek_soyad)
{
    for (int i = 0; i < (ogr_sayisi); i++)
        {
            if (strcmp(Ogrenciler[i].soyisim, silinecek_soyad) == 0 )
                {
                return &Ogrenciler[i];
                }
        }
            return NULL;
}


void silme(struct Ogrenci* Ogrenciler, int ogr_sayisi, char* silinecek_soyad)
{
    struct Ogrenci* silinecek = soyadBulma(Ogrenciler, ogr_sayisi, silinecek_soyad);
    if (silinecek != NULL)
        {
        for (int i = 0; i < ogr_sayisi; i++)
            {
            if (&Ogrenciler[i] == silinecek)
            {
                for (int j = i; j < ogr_sayisi - 1; j++)
                {
                    Ogrenciler[j] = Ogrenciler[j + 1];
                }
                ogr_sayisi--;
                break;
            }
            }
        }
}



void listele(struct Ogrenci Ogrenciler[], int ogr_sayisi){

      for (int i = 0; i < ogr_sayisi; i++)
        {
        for (int j = 0; j < Ogrenciler[i].ders_sayisi; j++)
            {
                printf("Ogrenci ID: %d, Isim: %s, Soyisim: %s, Ders Adi: %s, Ders Kodu: %s, Dersten Alinan Puan: %d\n\n",
                       Ogrenciler[i].ogrenci_id, Ogrenciler[i].isim, Ogrenciler[i].soyisim,
                       Ogrenciler[i].Dersler[j].d_ismi, Ogrenciler[i].Dersler[j].d_kodu, Ogrenciler[i].Dersler[j].d_puani) ;

            }
        }
}

int menu(int secim){

    printf("1-Listeleme\n2-Silme\n3-Arama\n4-Cikis\n") ;
    printf("seciminiz:");
    scanf("%d", &secim) ;
    printf("\n") ;
    return secim ;

}



int main()
{
    int temp = 0 ;


    FILE *file = fopen("ogrenciler.txt", "r");
    if (file == NULL) {
        perror("dosya acilamadi.");
        return 1;
        }


    struct Ogrenci Ogrenciler[35];
    int ogr_sayisi = 0;

     while (1) {
        char line[200];
        if (fgets(line, sizeof(line), file) == NULL) {
            break;
        }


        char isim[50];
        char soyisim[50];
        int ogrenci_id;
        char d_ismi[50];
        char d_kodu[10];
        int d_puani;


        if (sscanf(line, "%d, %49[^,], %49[^,], %49[^,], %49[^,], %d", &ogrenci_id, isim, soyisim, d_ismi, d_kodu, &d_puani) == 6) {
            int ogr_index = -1;
            for (int i = 0; i < ogr_sayisi; i++)
                {
                if (strcmp(Ogrenciler[i].isim, isim) == 0 && Ogrenciler[i].ogrenci_id == ogrenci_id)
                    {
                    // ogrenci eklenmis mi kontrolu
                    ogr_index = i;
                    break;
                    }
                }

            if (ogr_index == -1) {
                ogr_index = ogr_sayisi;
                Ogrenciler[ogr_sayisi].ogrenci_id = ogrenci_id;
                strcpy(Ogrenciler[ogr_sayisi].isim, isim);
                strcpy(Ogrenciler[ogr_sayisi].soyisim, soyisim);
                Ogrenciler[ogr_sayisi].ders_sayisi = 0;
                ogr_sayisi++;
                }

            strcpy((Ogrenciler[ogr_index].Dersler[Ogrenciler[ogr_index].ders_sayisi].d_ismi), (d_ismi));
            strcpy((Ogrenciler[ogr_index].Dersler[Ogrenciler[ogr_index].ders_sayisi].d_kodu), (d_kodu));
            Ogrenciler[ogr_index].Dersler[Ogrenciler[ogr_index].ders_sayisi].d_puani = d_puani ;
            Ogrenciler[ogr_index].ders_sayisi++;

        } else {
            printf("gecersiz: %s", line);
        }
    }

    fclose(file);


    while(temp<=0)
    {
        int secim = menu(secim) ;
        int t_secim ;
        switch(secim)
        {
            case 1:
                {
                //listele
                listele(Ogrenciler, ogr_sayisi) ;
                printf("Tekrar secim yapmak isterseniz 1'i tuslayin.\n->");
                scanf("%d",&t_secim);
                if(t_secim==1)
                {
                    temp=0;
                    break ;
                }
                else
                {
                    temp=1;
                    break ;
                }



            case 2:
                {
                //sil
                char* silinecek_soyad ;
                printf("silinmesini istedigin ogrencinin soyadi:");
                scanf("%s", &silinecek_soyad);
                silme(Ogrenciler, ogr_sayisi, silinecek_soyad);

                printf("Tekrar secim yapmak isterseniz 1'i tuslayin.\n->");
                scanf("%d",&t_secim);
                if(t_secim==1)
                {
                    temp=0;
                    break ;
                }
                else
                {
                    temp=1;
                    break ;
                }

                }


            case 3:
                {
                //ara
                char* arananKod ;
                printf("Aramak istediginiz ders kodu: ");
                scanf("%s", &arananKod);

                struct Ogrenci* result = kodBulma(Ogrenciler, ogr_sayisi, arananKod);

                if (result != NULL)
                {
                    printf("isim: %s ,soyisim: %s ,ID: %d ", result->isim, result->soyisim, result->ogrenci_id);
                    for (int j = 0; j < result->ders_sayisi; j++)
                        {
                        struct Ders* Dersler = &result->Dersler[j];
                        printf("dersin ismi: %s, alinan puan: %d", Dersler-> d_ismi, Dersler -> d_puani) ;
                        }
                }

                else
                {
                    printf("bulunamadi \n");
                }


                printf("Tekrar secim yapmak isterseniz 1'i tuslayin.\n->");
                scanf("%d",&t_secim);
                if(t_secim==1)
                {
                    temp=0;
                    break ;
                }
                else
                {
                    temp=1;
                    break ;
                }

                }


            case 4:
                {
                    temp = 1 ;
                    break ;
                }

              default :
                {
                    printf("Gecersiz tercih.");
                    break ;
                }

        }

        }

    }

     return 0 ;
}



