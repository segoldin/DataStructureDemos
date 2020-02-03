/* immigrationDemo.c 
 *
 *  Demo showing how tables (globally initialized arrays of structures)
 *  can be used to control program flow.
 *
 *  Copyright 2020 by Sally E. Goldin
 *
 *  May be freely copied and modified for educational purposes
 *  as long as this notice is retained in the header.
 *  Note this code is not intended for real-world applications.
 */

#include <stdio.h>
#include <string.h>

/* Information about visa rules for a country  */   
typedef struct
{
  char countryname[128];    /* full name */
  char code[4];             /* official 2 letter code, e.g. "US","TH"*/
  int touristMaxDays;       /* max number of days for a tourist visa*/
                            /* negative means people from this country
                               cannot get a tourist visa */
  int bizMaxDays;           /* max number of days for a business visa */
                            /* negative means people from this country
                               cannot get a business visa */
  int touristPrice;         /* cost for a tourist visa */
  int bizPrice;             /* cost for a business visa */
} COUNTRYINFO_T;


/*********** Global array of structs holding all visa information ****/
COUNTRYINFO_T countries[] = {
      {"Afghanistan","AF ",-1,-1,0,0},
      {"Aland Islands","AX",15,90,1000,3000},
      {"Albania","AL",10,15,1000,3000},
      {"Algeria","DZ",10,90,0,2500},
      {"American Samoa","AS",30,90,0,0},
      {"Andorra","AD",30,90,0,0},
      {"Angola","AO",10,30,1500,4000},
      {"Anguilla","AI",15,90,0,0},
      {"ANTIGUA AND BARBUDA","AG",-1,30,1000,2000},
      {"ARGENTINA","AR",10,30,1240,1900},
      {"ARMENIA","AM",10,30,900,1900},
      {"ARUBA","AW",10,60,900,2000},
      {"AUSTRALIA","AU",10,60,900,0},
      {"AUSTRIA","AT",10,60,1000,2000},
      {"AZERBAIJAN","AZ",-1,60,1240,2000},
      {"BAHAMAS","BS",15,30,1000,2000},
      {"BAHRAIN","BH",15,60,1000,1900},
      {"BANGLADESH","BD",15,30,1000,2000},
      {"BARBADOS","BB",15,60,900,0},
      {"BELARUS","BY",10,-1,1000,1900},
      {"BELGIUM","BE",10,60,900,2000},
      {"BELIZE","BZ",10,30,1240,2000},
      {"BENIN","BJ",15,60,1000,1900},
      {"BERMUDA","BM",10,30,900,0},
      {"BHUTAN","BT",15,-1,1000,2000},
      {"BOLIVIA","BO",10,60,900,0},
      {"BOSNIA AND HERZEGOVINA","BA",15,-1,900,1900},
      {"BOTSWANA","BW",10,30,1240,2000},
      {"BOUVET ISLAND","BV",15,60,1000,0},
      {"BRAZIL","BR",15,-1,900,2000},
      {"BRITISH VIRGIN ISLANDS","VG",10,-1,1000,1900},
      {"BRITISH INDIAN OCEAN TERRITORY","IO",15,-1,900,0},
      {"BRUNEI DARUSSALAM","BN",10,60,1000,2000},
      {"BULGARIA","BG",15,-1,1240,0},
      {"BURKINA FASO","BF",-1,-1,900,1900},
      {"BURUNDI","BI",15,60,1240,2000},
      {"CAMBODIA","KH",15,30,1240,2000},
      {"CAMEROON","CM",10,60,1240,0},
      {"CANADA","CA",15,-1,1240,1900},
      {"CAPE VERDE","CV",-1,60,0,0},
      {"CAYMAN ISLANDS","KY",15,-1,900,2000},
      {"CENTRAL AFRICAN REPUBLIC","CF",10,30,1000,0},
      {"CHAD","TD",15,-1,900,2000},
      {"CHILE","CL",10,60,1240,0},
      {"CHINA","CN",15,-1,1240,1900},
      {"HONG KONG","HK",10,30,1000,2000},
      {"MACAO","MO",15,60,1240,0},
      {"CHRISTMAS ISLAND","CX",15,30,900,2000},
      {"COLOMBIA","CO",-1,30,1000,0},
      {"COMOROS","KM",15,-1,1240,2000},
      {"CONGO (BRAZZAVILLE)","CG",10,60,900,0},
      {"CONGO, DEMOCRATIC REPUBLIC OF THE","CD",15,-1,1240,1900},
      {"COOK ISLANDS","CK",-1,60,1000,2000},
      {"COSTA RICA","CR",15,-1,1240,0},
      {"CÔTE D\'IVOIRE","CI",10,30,900,2000},
      {"CROATIA","HR",15,60,1240,0},
      {"CUBA","CU",-1-1,1000,1900},
      {"CYPRUS","CY",15,30,1240,0},
      {"CZECH REPUBLIC","CZ",10,60,900,2000},
      {"DENMARK","DK",15,30,1240,1900},
      {"DJIBOUTI","DJ",15,60,1000,0},
      {"DOMINICA","DM",10,-1,1240,2000},
      {"DOMINICAN REPUBLIC","DO",15,30,900,2000},
      {"ECUADOR","EC",10,-1,1240,0},
      {"EGYPT","EG",15,60,1240,1900},
      {"EL SALVADOR","SV",10,-1,900,0},
      {"EQUATORIAL GUINEA","GQ",15,30,1240,2000},
      {"ERITREA","ER",15,60,1000,2000},
      {"ESTONIA","EE",10,-1,1240,0},
      {"ETHIOPIA","ET",15,60,900,1900},
      {"FALKLAND ISLANDS (MALVINAS)","FK",10,-1,1240,0},
      {"FAROE ISLANDS","FO",15,30,1000,2000},
      {"FIJI","FJ",15,-1,1240,0},
      {"FINLAND","FI",10,60,900,1900},
      {"FRANCE","FR",15,-1,1240,0},
      {"FRENCH GUIANA","GF",10,30,1000,2000},
      {"FRENCH SOUTHERN TERRITORIES","TF",15,60,900,1900},
      {"GABON","GA",10,60,1240,2000},
      {"GAMBIA","GM",15,-1,1000,0},
      {"GEORGIA","GE",10,30,1240,2000},
      {"GERMANY","DE",15,60,900,0},
      {"GHANA","GH",10,-1,1240,1900},
      {"GIBRALTAR","GI",15,30,900,2000},
      {"GREECE","GR",10,60,1240,0},
      {"GREENLAND","GL",15,-1,0,1900},
      {"GRENADA","GD",15,60,1240,2000},
      {"GUADELOUPE","GP",10,-1,1240,0},
      {"GUAM","GU",15,30,900,2000},
      {"GUATEMALA","GT",10,-1,1240,0},
      {"GUERNSEY","GG",15,60,900,0},
      {"GUINEA","GN",10,30,1240,0},
      {"GUINEA-BISSAU","GW",15,-1,1000,1900},
      {"GUYANA","GY",15,60,1240,0},
      {"HAITI","HT 2",10,-1,900,2000},
      {"HEARD ISLAND AND MCDONALD ISLANDS","HM",15,60,1240,0},
      {"HOLY SEE (VATICAN CITY STATE)","VA",10,-1,1240,1900},
      {"HONDURAS","HN",15,30,1240,2000},
      {"HUNGARY","HU",10,60,1000,0},
      {"ICELAND","IS",15,30,1240,1900},
      {"INDIA","IN",10,60,900,0},
      {"INDONESIA","ID",15,60,1240,2000},
      {"IRAN, ISLAMIC REPUBLIC OF","IR",10,-1,1000,1900},
      {"IRAQ","IQ",15,30,1240,0},
      {"IRELAND","IE",10,-1,1240,2000},
      {"ISLE OF MAN","IM",15,60,900,0},
      {"ISRAEL","IL",15,-1,1240,2000},
      {"ITALY","IT",10,60,900,1900},
      {"JAMAICA","JM",15,30,1240,0},
      {"JAPAN","JP",10,-1,1000,2000},
      {"JERSEY","JE",15,60,1240,0},
      {"JORDAN","JO",10,-1,900,1900},
      {"KAZAKHSTAN","KZ",15,30,1240,0},
      {"KENYA","KE",10,-1,1240,2000},
      {"KIRIBATI","KI",15,60,900,2000},
      {"KOREA, DEMOCRATIC PEOPLE\'S REPUBLIC OF","KP",15,-1,1240,0},
      {"KOREA, REPUBLIC OF","KR",10,60,1000,1900},
      {"KUWAIT","KW",15,-1,1240,0},
      {"KYRGYZSTAN","KG",10,30,900,2000},
      {"LAO PDR","LA",15,-1,1240,2000},
      {"LATVIA","LV",10,60,1240,0},
      {"LEBANON","LB",15,-1,1000,2000},
      {"LESOTHO","LS",10,60,1240,0},
      {"LIBERIA","LR",15,-1,900,1900},
      {"LIBYA","LY",10,60,1240,2000},
      {"LIECHTENSTEIN","LI",15,60,1240,0},
      {"LITHUANIA","LT",10,-1,1000,1900},
      {"LUXEMBOURG","LU",15,60,1240,0},
      {"MACEDONIA, REPUBLIC OF","MK",15,-1,1240,1900},
      {"MADAGASCAR","MG",10,30,1240,1900},
      {"MALAWI","MW",15,-1,900,0},
      {"MALAYSIA","MY",10,60,1240,1900},
      {"MALDIVES","MV",15,30,1240,0},
      {"MALI","ML",15,-1,1240,2000},
      {"MALTA","MT",10,60,900,1900},
      {"MARSHALL ISLANDS","MH",15,-1,1240,0},
      {"MARTINIQUE","MQ",15,25,1240,200},
      {"MAURITANIA","MR",10,30,0,2000},
      {"MAURITIUS","MU",15,-1,1240,0},
      {"MAYOTTE","YT",10,60,900,1900},
      {"MEXICO","MX",15,-1,1240,0},
      {"MICRONESIA, FEDERATED STATES OF","FM",10,60,1000,2000},
      {"MOLDOVA","MD",15,-1,1240,0},
      {"MONACO","MC",10,30,900,1900},
      {"MONGOLIA","MN",10,-1,1240,0},
      {"MONTENEGRO","ME",10,60,1240,2000},
      {"MONTSERRAT","MS",10,-1,900,1900},
      {"MOROCCO","MA",15,30,1240,0},
      {"MOZAMBIQUE","MZ",15,-1,1240,2000},
      {"MYANMAR","MM",15,60,0,0},
      {"NAMIBIA","NA",15,-1,1240,1900},
      {"NAURU","NR",15,60,900,0},
      {"NEPAL","NP",15,-1,1240,2000},
      {"NETHERLANDS","NL",10,30,1240,0},
      {"NETHERLANDS ANTILLES","AN",15,-1,1000,1900},
      {"NEW CALEDONIA","NC",10,60,1240,2000},
      {"NEW ZEALAND","NZ",15,30,1240,1900},
      {"NICARAGUA","NI",10,-1,900,0},
      {"NIGER","NE",15,60,1240,2000},
      {"NIGERIA","NG",15,-1,1240,0},
      {"NIUE","NU",10,30,1000,2000},
      {"NORFOLK ISLAND","NF",15,60,1240,1900},
      {"NORTHERN MARIANA ISLANDS","MP",10,-1,1240,0},
      {"NORWAY","NO",15,30,900,2000},
      {"OMAN","OM",10,-1,1240,2000},
      {"PAKISTAN","PK",15,60,1240,0},
      {"PALAU","PW",10,60,900,1900},
      {"PALESTINIAN TERRITORY, OCCUPIED","PS",15,-1,1240,2000},
      {"PANAMA","PA",10,30,0,0},
      {"PAPUA NEW GUINEA","PG",15,-1,1240,1900},
      {"PARAGUAY","PY",10,60,1240,0},
      {"PERU","PE",15,30,900,2000},
      {"PHILIPPINES","PH",15,-1,1240,1900},
      {"PITCAIRN","PN",10,60,1000,0},
      {"POLAND","PL",15,-1,1240,2000},
      {"PORTUGAL","PT",10,60,1240,1900},
      {"PUERTO RICO","PR",15,-1,900,0},
      {"QATAR","QA",15,30,1240,2000},
      {"RÉUNION","RE",10,-1,1240,1900},
      {"ROMANIA","RO",15,60,0,0},
      {"RUSSIAN FEDERATION","RU",10,-1,1240,2000},
      {"RWANDA","RW",15,30,900,0},
      {"SAINT-BARTHÉLEMY","BL",15,-1,1240,1900},
      {"SAINT HELENA","SH",10,60,1240,2000},
      {"SAINT KITTS AND NEVIS","KN",15,60,900,0},
      {"SAINT LUCIA","LC",10,-1,1240,2000},
      {"SAINT-MARTIN (FRENCH PART)","MF",15,-1,1240,1900},
      {"SAINT PIERRE AND MIQUELON","PM",15,30,1000,0},
      {"SAINT VINCENT AND GRENADINES","VC",10,-1,1240,2000},
      {"SAMOA","WS",15,60,900,1900},
      {"SAN MARINO","SM",10,-1,1240,0},
      {"SAO TOME AND PRINCIPE","ST",15,30,1240,2000},
      {"SAUDI ARABIA","SA",10,-1,0,0},
      {"SENEGAL","SN",15,60,1240,2000},
      {"SERBIA","RS",15,60,900,1900},
      {"SEYCHELLES","SC",10,-1,1240,0},
      {"SIERRA LEONE","SL",15,30,1000,2000},
      {"SINGAPORE","SG",10,-1,1240,0},
      {"SLOVAKIA","SK",15,60,1240,1900},
      {"SLOVENIA","SI",10,-1,900,0},
      {"SOLOMON ISLANDS","SB",15,60,1240,2000},
      {"SOMALIA","SO",10,30,900,1900},
      {"SOUTH AFRICA","ZA",15,-1,1240,0},
      {"SOUTH GEORGIA AND THE SOUTH SANDWICH ISLANDS","GS",15,60,1240,2000},
      {"SOUTH SUDAN","SS",10,-1,0,0},
      {"SPAIN","ES",15,30,1240,2000},
      {"SRI LANKA","LK",10,-1,1240,1900},
      {"SUDAN","SD",15,60,900,0},
      {"SURINAME ","SR",10,-1,1240,2000},
      {"SVALBARD AND JAN MAYEN ISLANDS","SJ",15,30,1000,0},
      {"SWAZILAND","SZ",10,-1,1240,1900},
      {"SWEDEN","SE",15,60,1240,0},
      {"SWITZERLAND","CH",15,-1,900,2000},
      {"SYRIAN ARAB REPUBLIC (SYRIA)","SY",10,60,1240,1900},
      {"TAIWAN, REPUBLIC OF CHINA","TW",15,-1,1240,0},
      {"TAJIKISTAN","TJ",10,30,1240,2000},
      {"TANZANIA, UNITED REPUBLIC OF","TZ",15,-1,900,0},
      {"TIMOR-LESTE","TL",10,60,1240,2000},
      {"TOGO","TG",15,-1,1240,0},
      {"TOKELAU","TK",10,30,0,1900},
      {"TONGA","TO",15,-1,1240,0},
      {"TRINIDAD AND TOBAGO","TT",10,60,900,2000},
      {"TUNISIA","TN",15,-1,1240,1900},
      {"TURKEY","TR",10,30,1240,0},
      {"TURKMENISTAN","TM",15,-1,900,2000},
      {"TURKS AND CAICOS ISLANDS","TC",10,60,1240,1900},
      {"TUVALU","TV",15,-1,1000,0},
      {"UGANDA","UG",10,60,1500,-100},
      {"UKRAINE","UA",15,90,0,0},
      {"UNITED ARAB EMIRATES","AE",30,180,0,0},
      {"UNITED KINGDOM","GB",-1,180,0,0},
      {"UNITED STATES OF AMERICA","US",60,180,0,0},
      {"URUGUAY","UY",30,90,1240,1240},
      {"Uzbekistan","UZ",15,-1,900,0},
      {"Vanuatu","VU",15,90,0,0},
      {"Venezuela (Bolivarian Republic of)","VE",15,-1,1240,2000},
      {"Viet Nam","VN",10,60,0,0},
      {"Yemen","YE",-1,180,0,0},
      {"Zambia","ZM",15,30,1900,2000},
      {"Zimbabwe","ZW",15,-1,0,1900}};

int countryCount = sizeof(countries)/sizeof(COUNTRYINFO_T);


/* Print how much the user owes, based on the country and the type of visa.
 * Also tell the user how many days he can stay in Thailand.
 *    code        - two letter code for the user's country
 *    bTourist    - if 1, they want a tourist visa, if 0, a business visa
 */
void getVisaPrice(int bTourist,char* code)
   {
   int i;
   for (i = 0; i < countryCount; i++)
       {
       if (strcasecmp(countries[i].code,code) == 0)
           {
           printf("As a citizen of %s: \n",countries[i].countryname);
           if (bTourist)
               {
	       if (countries[i].touristMaxDays > 0)
                  {
		  printf("Your TOURIST visa will cost %d baht\n",countries[i].touristPrice);
                  printf("You can stay in Thailand for %d days\n",countries[i].touristMaxDays);
                  }
               else
                  printf("You are not allowed to visit Thailand as a tourist\n");
               } 
           else
               {
	       if (countries[i].bizMaxDays > 0)
                  {
	          printf("Your BUSINESS visa will cost %d baht\n",countries[i].bizPrice);
                  printf("You can stay in Thailand for %d days\n",countries[i].bizMaxDays);
                  }
               else
                  printf("You are not allowed to visit Thailand for business\n");
               }
           break; /* we have found the country, so do not look further */
           }
       }
   if (i >= countryCount) /* not found */
       printf("No information found for code %s\n", code);
   } 

/* Main function asks for country code, looks up visa info */
int main()
{
  char inputline[32];    /* buffer for terminal input */
  char countryCode[4];   /* country of interest */
  int visaOption = 0;    /* 0 for business, 1 for tourist, 2 to exit */
  while (visaOption != 2)
    {
    printf("\t1 Business visa\n\t2 Tourist via\n\t3 Finished\n");  
    printf("Select visa type: ");
    fgets(inputline,sizeof(inputline),stdin);
    sscanf(inputline,"%d",&visaOption);
    visaOption -=1; /* so we can use as input to getVisaPrice, which expects tourist=1 */
    if ((visaOption == 0) || (visaOption == 1))
       {
       printf("Please enter your two letter country code: ");
       fgets(inputline,sizeof(inputline),stdin);
       sscanf(inputline,"%s",countryCode);
       printf("\n");
       getVisaPrice(visaOption,countryCode); 
       printf("\n");
       }
    }
}
