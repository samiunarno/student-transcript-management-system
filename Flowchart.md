        +-------------------+
        |      START        |
        +---------+---------+
                  |
                  v
        +-------------------+
        | Enter Username &  |
        | Password          |
        +---------+---------+
                  |
                  v
        +-------------------+
        | validateUser()    |
        +---------+---------+
                  |
        +---------+---------+
        |                   |
       YES                 NO
        |                   |
        v                   v
+---------------+     +----------------+
| Load File     |     | Login Failed   |
| (students.txt)|     | Exit Program   |
+-------+-------+     +----------------+
        |
        v
+------------------------+
|        MENU            |
| 1.Load 2.Display       |
| 3.Add  4.Search        |
| 5.Delete 6.Sort        |
| 7.Save 0.Exit          |
+-----------+------------+
            |
   -------------------------
   |   |    |    |    |    |
   v   v    v    v    v    v

Load Display Add Search Delete Sort Save
 |     |     |     |      |     |    |
 v     v     v     v      v     v    v

Linked List Operations (RAM)

            |
            v
     +--------------+
     | SaveToFile() |
     +------+-------+
            |
            v
        +-------+
        |  END  |
        +-------+