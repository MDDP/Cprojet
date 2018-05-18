#include <check.h>
#include "buffer.h" // SUT

START_TEST(test_init_buff1)
{
  buffer * buff = initialisation(-1,12);
  
	ck_assert_msg (buff == NULL, "On attendait NULL.");
}
END_TEST

START_TEST(test_init_buff2)
{
  buffer * buff = initialisation(20,0);
  
	ck_assert_msg (buff == NULL, "On attendait NULL.");
}
END_TEST

START_TEST(test_init_buff3)
{
  buffer * buff = initialisation(60,10);

	ck_assert_msg (buff != NULL && buff->taille == 60, "On attendait un buffer initialisé vide de taille 60");
}
END_TEST

START_TEST(test_dep_buff1)
{
  buffer * buff = initialisation(60,10);
  chargement(buff, "test.txt");
  deplacerA(0, buff);
	ck_assert_msg (
		buff->cur_char == 0 && buff->posX == 0 && buff->posY == 0,
		"Attendu: 0 0 0, reçu: %d %d %d", buff->cur_char, buff->posX, buff->posY
	);
}
END_TEST

START_TEST(test_dep_buff2)
{
  buffer * buff = initialisation(60,10);
  chargement(buff, "test.txt");
  deplacerA(0,buff);
  deplacer(15, buff);
  ck_assert_msg (
		buff->cur_char == 15 && buff->posX == 5 && buff->posY == 1,
		"Attendu: 10 5 1, reçu: %d %d %d", buff->cur_char, buff->posX, buff->posY
	);
}
END_TEST

START_TEST(test_dep_buff3)
{
  buffer * buff = initialisation(60,10);
  chargement(buff, "test.txt");
  deplacerA(10,buff);
  deplacer(-5, buff);
	ck_assert_msg (
		buff->cur_char == 5 && buff->posX == 5 && buff->posY == 0,
		"Attendu: 10 5 1, reçu: %d %d %d", buff->cur_char, buff->posX, buff->posY
	);
}
END_TEST

START_TEST(test_dep_buff4)
{
  buffer * buff = initialisation(60,10);
  chargement(buff, "test.txt");
  int tmp = deplacer(1, buff);
	ck_assert_msg (
		buff->cur_char == 51 && buff->posX == 3 && buff->posY == 5 && tmp == -1,
		"Attendu: -1 et buffer inchangé, reçu: %d", tmp
	);
}
END_TEST

START_TEST(test_dep_buff5)
{
  buffer * buff = initialisation(60,10);
  chargement(buff, "test.txt");
  int tmp = deplacer(-60, buff);
	ck_assert_msg (
		buff->cur_char == 51 && buff->posX == 3 && buff->posY == 5 && tmp == -1,
		"Attendu: -1 et buffer inchangé, reçu: %d", tmp
	);
}
END_TEST

START_TEST(test_dep_buff6)
{
  buffer * buff = initialisation(60,10);
  chargement(buff, "test.txt");
  int tmp = deplacerA(-1, buff);
	ck_assert_msg (
		buff->cur_char == 51 && buff->posX == 3 && buff->posY == 5 && tmp == 0,
		"Attendu: 0, reçu: %d", tmp
	);
}
END_TEST

START_TEST(test_charg_buff1)
{
  buffer * buff = initialisation(60,10);
  chargement(buff, "test.txt");
	ck_assert_msg (
		strcmp(buff->contenu, "Ceci est un fichier de test\nJuste hsitoire de voire") == 0,
		"Fichier mal lu"
	);
}
END_TEST

START_TEST(test_charg_buff2)
{
  buffer * buff = initialisation(60,10);
  int i = chargement(buff, "tes.txt");
  
	ck_assert_msg (
		i == 0,
		"N'est pas sensé lire"
	);
}
END_TEST

START_TEST(test_ecri_buff1)
{
  buffer * buff = initialisation(20,10);
  char *aEcrire = "Bonjour";
  for (int i = 0; i < strlen(aEcrire); i++)
    ecrire(*(aEcrire+i), buff);
  
  
	ck_assert_msg (
		strcmp(buff->contenu, aEcrire) == 0,
		"Attendu : [%s], reçu: [%s]", aEcrire, buff->contenu
	);
}
END_TEST

START_TEST(test_ecri_buff2)
{
  buffer * buff = initialisation(20,10);
  char *aEcrire = "Bonjour, ceci est une phrase longue";
  for (int i = 0; i < strlen(aEcrire); i++)
    ecrire(*(aEcrire+i), buff);
  
	ck_assert_msg (
		strcmp(buff->contenu, aEcrire) == 0,
		"Attendu : [%s], reçu: [%s]", aEcrire, buff->contenu
	);
}
END_TEST

START_TEST(test_ecri_buff3)
{
  buffer * buff = initialisation(60,10);
  char *aEcrire = "Bonjour";
  for (int i = 0; i < strlen(aEcrire); i++)
    ecrire(*(aEcrire+i), buff);
  deplacerA(0, buff);
  aEcrire = "Au revoir";
  for (int i = 0; i < strlen(aEcrire); i++)
    ecrire(*(aEcrire+i), buff);
  
	ck_assert_msg (
		strcmp(buff->contenu, aEcrire) == 0,
		"Attendu : [%s], reçu: [%s]", aEcrire, buff->contenu
	);
}
END_TEST

START_TEST(test_inser_buff1)
{
  buffer * buff = initialisation(20,10);
  char *aEcrire = "Bonjour";
  for (int i = 0; i < strlen(aEcrire); i++)
    insertion(*(aEcrire+i), buff);
  
	ck_assert_msg (
		strcmp(buff->contenu, aEcrire) == 0,
		"Attendu : [%s], reçu: [%s]", aEcrire, buff->contenu
	);
}
END_TEST

START_TEST(test_inser_buff2)
{
  buffer * buff = initialisation(20,10);
  char *aEcrire = "Bonjour";
  for (int i = 0; i < strlen(aEcrire); i++)
    insertion(*(aEcrire+i), buff);
  deplacerA(0, buff);
  char *aEcrirebis = "Oh! Bonjour";
  for (int i = 0; i < 4; i++)
    insertion(*(aEcrirebis+i), buff);
  
	ck_assert_msg (
		strcmp(buff->contenu, aEcrirebis) == 0,
		"Attendu : [%s], reçu: [%s]", aEcrirebis, buff->contenu
	);
}
END_TEST

START_TEST(test_inser_buff3)
{
  buffer * buff = initialisation(20,10);
  char *aEcrire = "Bonjour";
  for (int i = 0; i < strlen(aEcrire); i++)
    insertion(*(aEcrire+i), buff);
  char *aEcrirebis = "Bonjour, salut";
  for (int i = 7; i < strlen(aEcrirebis); i++)
    insertion(*(aEcrirebis+i), buff);
  
	ck_assert_msg (
		strcmp(buff->contenu, aEcrirebis) == 0,
		"Attendu : [%s], reçu: [%s]", aEcrirebis, buff->contenu
	);
}
END_TEST

START_TEST(test_inser_buff4)
{
  buffer * buff = initialisation(20,10);
  char *aEcrire = "Vige";
  for (int i = 0; i < strlen(aEcrire); i++)
    insertion(*(aEcrire+i), buff);
  deplacerA(2, buff);
  char *aEcrirebis = "Viens à la plage";
  for (int i = 2; i < 15; i++)
    insertion(*(aEcrirebis+i), buff);
  
	ck_assert_msg (
		strcmp(buff->contenu, aEcrirebis) == 0,
		"Attendu : [%s], reçu: [%s]", aEcrirebis, buff->contenu
	);
}
END_TEST

START_TEST(test_suppr_buff1)
{
  buffer * buff = initialisation(20,10);
  supprimer(buff);
  
	ck_assert_msg (
		strcmp(buff->contenu, "") == 0,
		"Attendu : [%s], reçu: [%s]", "", buff->contenu
	);
}
END_TEST

START_TEST(test_suppr_buff2)
{
  buffer * buff = initialisation(20,10);
  char *aEcrire = "Vige";
  for (int i = 0; i < strlen(aEcrire); i++)
    insertion(*(aEcrire+i), buff);
  deplacerA(2, buff);
  supprimer(buff);
  
	ck_assert_msg (
		strcmp(buff->contenu, "Vie") == 0,
		"Attendu : [%s], reçu: [%s]", "Vie", buff->contenu
	);
}
END_TEST

START_TEST(test_suppr_buff3)
{
  buffer * buff = initialisation(20,10);
  char *aEcrire = "Vige";
  for (int i = 0; i < strlen(aEcrire); i++)
    insertion(*(aEcrire+i), buff);
  supprimer(buff);
  
	ck_assert_msg (
		strcmp(buff->contenu, aEcrire) == 0,
		"Attendu : [%s], reçu: [%s]", aEcrire, buff->contenu
	);
}
END_TEST

START_TEST(test_suppr_buff4)
{
  buffer * buff = initialisation(10,10);
  char *aEcrire = "Vige";
  for (int i = 0; i < strlen(aEcrire); i++)
    ecrire(*(aEcrire+i), buff);
  deplacerA(0, buff);
  supprimer(buff);
  
	ck_assert_msg (
		strcmp(buff->contenu, "ige") == 0,
		"Attendu : [%s] , reçu: [%s]", "ige", buff->contenu
	);
}
END_TEST

Suite * buffer_suite(void)
{
  Suite *s;
  TCase *tc_init;
  TCase *tc_dep;
  TCase *tc_charg;
  TCase *tc_ecri;
  TCase *tc_inser;
  TCase *tc_suppr;

  s = suite_create("Buffer");

  tc_init = tcase_create("Intialisation");
  tcase_add_test(tc_init, test_init_buff1);
  tcase_add_test(tc_init, test_init_buff2);
  tcase_add_test(tc_init, test_init_buff3);
  
  tc_dep = tcase_create("Deplacement");
  tcase_add_test(tc_dep, test_dep_buff1);
  tcase_add_test(tc_dep, test_dep_buff2);
  tcase_add_test(tc_dep, test_dep_buff3);
  tcase_add_test(tc_dep, test_dep_buff4);
  tcase_add_test(tc_dep, test_dep_buff5);
  tcase_add_test(tc_dep, test_dep_buff6);

  tc_charg = tcase_create("Chargement");
  tcase_add_test(tc_charg, test_charg_buff1);
  tcase_add_test(tc_charg, test_charg_buff2);
  
  tc_ecri = tcase_create("Ecriture");
  tcase_add_test(tc_ecri, test_ecri_buff1);
  tcase_add_test(tc_ecri, test_ecri_buff2);
  tcase_add_test(tc_ecri, test_ecri_buff3);
  
  tc_inser = tcase_create("Insertion");
  tcase_add_test(tc_inser, test_inser_buff1);
  tcase_add_test(tc_inser, test_inser_buff2);
  tcase_add_test(tc_inser, test_inser_buff3);
  tcase_add_test(tc_inser, test_inser_buff4);
  
  tc_suppr = tcase_create("Insertion");
  tcase_add_test(tc_suppr, test_suppr_buff1);
  tcase_add_test(tc_suppr, test_suppr_buff2);
  tcase_add_test(tc_suppr, test_suppr_buff3);
  tcase_add_test(tc_suppr, test_suppr_buff4);
  
  
  suite_add_tcase(s, tc_init);
  suite_add_tcase(s, tc_charg);
  suite_add_tcase(s, tc_dep);
  suite_add_tcase(s, tc_ecri);
  suite_add_tcase(s, tc_inser);
  suite_add_tcase(s, tc_suppr);

  return s;
}

int main () {
  int number_failed;
  Suite *s;
  SRunner *sr;

  s = buffer_suite();
  sr = srunner_create(s);

  srunner_run_all(sr, CK_NORMAL);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}