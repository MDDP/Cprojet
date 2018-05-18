#include <check.h>
#include "configuration.h"

START_TEST(test_actu_config1)
{
  char control[NBCONFIG];
  actualiseConfig(control);

  ck_assert_msg
    (
     control[0] == 'l',
     "On attendait [%c], mais on a obtenu [%c]",
     'l', control[0]
     );
}
END_TEST

START_TEST(test_actu_config2)
{
  char control[NBCONFIG];
  actualiseConfig(control);

  ck_assert_msg
    (
     control[7] == 'e',
     "On attendait [%c], mais on a obtenu [%c]",
     'e', control[7]
     );
}
END_TEST

START_TEST(test_sauv_config1)
{
  char temoin[NBCONFIG];
  actualiseConfig(temoin);

  char control[NBCONFIG];
  actualiseConfig(control);
  control[0] = 'y';
  control[5] = 'u';
  sauvegardeConfig(control);

  ck_assert_msg
    (
     control[0] == 'y',
     "On attendait [%c], mais on a obtenu [%c]",
     'y', control[0]
     );

  ck_assert_msg
    (
     control[5] == 'u',
     "On attendait [%c], mais on a obtenu [%c]",
     'u', control[5]
     );

  sauvegardeConfig(temoin);
}
END_TEST

START_TEST(test_sauv_config2)
{
  char temoin[NBCONFIG];
  actualiseConfig(temoin);

  char control[NBCONFIG];
  actualiseConfig(control);
  control[0] = 'x';
  sauvegardeConfig(control);

  char verif[NBCONFIG];
  actualiseConfig(verif);

  ck_assert_msg
    (
     verif[0] == 'l',
     "On attendait [%c], mais on a obtenu [%c]",
     'l', verif[0]
     );

  sauvegardeConfig(temoin);
}
END_TEST

START_TEST(test_sauv_config3)
{
  char temoin[NBCONFIG];
  actualiseConfig(temoin);

  char control[NBCONFIG];
  actualiseConfig(control);
  control[7] = 'l';
  sauvegardeConfig(control);

  char verif[NBCONFIG];
  actualiseConfig(verif);

  ck_assert_msg
    (
     verif[7] == 'e',
     "On attendait [%c], mais on a obtenu [%c]",
     'e', verif[0]
     );

  sauvegardeConfig(temoin);
}
END_TEST

Suite * config_suite(void)
{
  Suite *s;
  TCase *tc_core;

  s = suite_create("Config");

  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_actu_config1);
  tcase_add_test(tc_core, test_actu_config2);
  tcase_add_test(tc_core, test_sauv_config1);
  tcase_add_test(tc_core, test_sauv_config2);
  tcase_add_test(tc_core, test_sauv_config3);

  suite_add_tcase(s, tc_core);

  return s;
}

int main(void)
{
  int number_failed;
  Suite *s;
  SRunner *sr;

  s = config_suite();
  sr = srunner_create(s);

  srunner_run_all(sr, CK_NORMAL);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
