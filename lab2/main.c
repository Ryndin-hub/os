#include <sys/types.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

main() {
    //putenv добавляет значение или модифицирует существующие переменные окружения, после выполнения программы вернётся в изначальное состояние
    //Калифорнию не найти, поэтому поставил город на том-же часовом поясе
    //возвращает 0 если отработало успешно и 1 при ошибке
    if(putenv("TZ=America/Los_Angeles") != 0){
        perror("Error while setting TZ environment variable");
        exit(1);
    }

    time_t now;
    struct tm *sp;

    //записывает текущее календарное время системы в переменную типа time_t
    (void) time(&now);

    //ctime возвращает указатель на строку формата (день месяц дата часы:минуты:секунды год)
    printf("%s", ctime(&now));

    //localtime преобразует из time_t now в структуру tm и возвращает указатель на неё, счёт годов идёт с 1900
    //чтобы устанавить значения daylight, timezone, tzname - localtime вызывает tzset, если не удаётся то по умолчанию считает как тихоокеанский часовой пояс
    //daylight - часовой пояс для летнего времени, timezone - разница от UTC, tzname[0] - имя часового пояса, tzname[1] - летнее время, PDT - по умолчанию
    sp = localtime(&now);

    //tm_mon - месяц, tm_mday - день месяца и т.д. , tm_isdst - 1 если есть летнее время, 0 если нет
    //tzname[sp->tm_isdst] будет выводить либо летнее время при его наличии, либо имя часового пояса
    printf("%d/%d/%02d %d:%02d %s\n",
           sp->tm_mon + 1, sp->tm_mday,
           sp->tm_year, sp->tm_hour,
           sp->tm_min, tzname[sp->tm_isdst]);
    exit(0);
}
