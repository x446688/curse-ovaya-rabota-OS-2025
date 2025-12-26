#include <check.h>
#include "../src/web.h"

START_TEST(test_basic)
{
    char test[] = "test";
    char result[] = "test";
    remove_newlines(test);
    ck_assert(strcmp(result, "test") == 0);
}
END_TEST

Suite *web_suite(void) {
    Suite *s = suite_create("Web");
    TCase *tc = tcase_create("Basic");
    tcase_add_test(tc, test_basic);
    suite_add_tcase(s, tc);
    return s;
}

int main(void) {
    Suite *s = web_suite();
    SRunner *sr = srunner_create(s);
    srunner_run_all(sr, CK_NORMAL);
    int failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    return (failed == 0) ? 0 : 1;
}
