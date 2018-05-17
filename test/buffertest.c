#include <check.h>
#include "../src/buffer.h" // SUT

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

Suite * buffer_suite(void)
{
  Suite *s;
  TCase *tc_init;
  TCase *tc_dep;
  TCase *tc_charg;

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

  tc_charg = tcase_create("Chargemetn");
  tcase_add_test(tc_charg, test_charg_buff1);
  tcase_add_test(tc_charg, test_charg_buff2);
  
  suite_add_tcase(s, tc_init);
  suite_add_tcase(s, tc_charg);
  suite_add_tcase(s, tc_dep);

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