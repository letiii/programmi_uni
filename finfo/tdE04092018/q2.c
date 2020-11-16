#define N 12
typedef struct rilevazioni_s{
	float temperatura;
	int umidita;
	char tempo[N+1];
	struct rilevazioni_s * next;
}rilevazioni_t;