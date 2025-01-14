**BÁO CÁO GAME MINESWEEPER**

> Tên: Đinh HồGia Huy\
> MSSV: 23125036\
> Lớp: 23TT1
>
> **1. Những tính năng đã hoàn thành:**\
> Tính năng đã hoàn thành:\
> **Basic features:**\
> 1. Drawing the board (including cells, mines and flags).
>
> 2\. Changing the state of each cell when it is selected.
>
> 3\. Timer.
>
> 4\. Functions: new game, change board dimensions. Select a function
> from the console screen.
>
> 5\. Randomize positions of the mines.
>
> 6\. Receiving a new position of the pointer (to select a cell) from
> the console screen.
>
> 7\. Saving the current state of the board and loading in the next
> playing session.
>
> 8\. Saving high scores.
>
> **Other features:**\
> - Using keyboard (arrow keys) to select a cell.\
> - Using struct.
>
> Tính năng chưa hoàn thành:\
> - Rendering images: em không dùng hình ảnh ngoài mà chỉdùng console.
>
> **2. Cấu trúc mã nguồn:**\
> Source file em có các file sau:\
> - **main.cpp**: file chứa hàm main, em dùng hàm chỉnh lại kích thước
> console, gọi hàm vẽtiêu đềvà vẽmenu chính, gọi hàm xửlý sựkiện nhập
> từbàn phím\
> - **main.h**: file header cho file main.cpp, em đặt các struct trong
> file này, gồm 3 struct là Board, Cell, Timer.
>
> \- **Console.cpp**: chứa hàm xửlý màn hình console\
> - **Console.h**: header file cho file Console.cpp, gọi header file
> windows.h- **functions.cpp**: file chứa những function chính đểxửlý
> sựkiện game, in text ra màn hình console, được chia ra theo chức năng
> bằng comment.

+-----------------------------------+-----------------------------------+
| \-                                | > **functions.h**: header file    |
|                                   | > cho file functions.cpp          |
+===================================+===================================+
+-----------------------------------+-----------------------------------+

> **3. Hướng dẫn sửdụng:**\
> (\*LƯU Ý: không biết sao khi em chạy chương trình trong solution thì
> không sao nhưng em chạy bằng file .exe thỉnh thoảng màn hình menu nó
> bịlỗi như bên dưới. Thầy thoát ra vào lại 1 vài lần thì nó sẽbình
> thường ạ(nhưng sau đấy vẫn sẽbịlại).

![](vertopal_8a88c408b64841bc9473e6d0dfb0f645/media/image1.png){width="6.270833333333333in"
height="3.301388888888889in"}

> **ĐIỀU KHIỂN TRONG GAME ỞTẤT CẢMÀN HÌNH**

+-----------------------------------+-----------------------------------+
| > \-\                             | > sửdụng những phím mũi tên lên,  |
| > -\                              | > xuống, trái, phải đểđiều hướng, |
| > -\                              | > phím Enter đểchọn,\             |
| > -                               | > phím ESC đểthoát.               |
|                                   | >                                 |
|                                   | > phím A đểmởô, phím D đểcắm cờ   |
+===================================+===================================+
+-----------------------------------+-----------------------------------+

> **Màn hình chính**: gồm các phím chức năng:\
> +New game : bắt đầu game mới\
> +Resume game : chơi game được lưu\
> +Highscore: xem bảng điểm highscore\
> + Quit : thoát game, cũng có thểthoát bằng phím ESC
>
> ![](vertopal_8a88c408b64841bc9473e6d0dfb0f645/media/image2.png){width="6.270832239720035in"
> height="4.113888888888889in"}
>
> **NEW GAME:**\
> Dùng mũi tên lên xuống đểđiều hướng, enter đểchọn Màn hình chọn độkhó,
> có 3 mức độ.
>
> ![](vertopal_8a88c408b64841bc9473e6d0dfb0f645/media/image3.png){width="6.270833333333333in"
> height="3.6972222222222224in"}
>
> **CHẾĐỘCUSTOM TẠO MAP RIÊNG**\
> - Nhập vào chiều cao, chiều rộng, sốbom của map
>
> ![](vertopal_8a88c408b64841bc9473e6d0dfb0f645/media/image4.png){width="6.270833333333333in"
> height="3.448611111111111in"}
>
> \- Nếu nhập thông sốvô lý (sốbom nhiều hơn kích cỡ, nhập sốâm), in ra
> thông báo lỗi, và yêu cầu nhập lại.
>
> ![](vertopal_8a88c408b64841bc9473e6d0dfb0f645/media/image5.png){width="6.270833333333333in"
> height="3.9166666666666665in"}

+-----------------------------------+-----------------------------------+
| \-                                | > Không dùng esc được ởmàn hình   |
|                                   | > này, chỉthoát khi nhập map hợp  |
|                                   | > lệ.                             |
+===================================+===================================+
+-----------------------------------+-----------------------------------+

> **MÀN HÌNH CHƠI GAME:**\
> - Điều khiển: dùng mũi tên đểđiều hướng, phím A đểmởô, phím D đểđặt
> cờ.
>
> \- Hiện kích cỡmạp, sốbom, thời gian hiện sốgiây từlúc bắt đầu, trạng
> thái game nếu đang chơi sẽhiện "PLAYING".
>
> Con trỏmàu tím, vịtrí bắt đầu của con trỏởô trên cùng bên trái.-\
> - Vịtrí ởmỗi lần chơi sẽkhác nhau\
> - Sốbom sẽđược cập nhật : sốbom giảm đi 1 với mỗi lá cờđược cắm. (em
> thấy minesweeper gốc, nếu mình cắm nhiều cờhơn sốbom thì sốbom sẽ hiện
> là sốâm chứkhông hiện là 0 nên em cx làm vậy)\
> Ô chữ"P" là ô đặt cờ.-
>
> ![](vertopal_8a88c408b64841bc9473e6d0dfb0f645/media/image6.png){width="6.270833333333333in"
> height="4.9902766841644794in"}

+-----------------------------------+-----------------------------------+
| \-                                | > Khí nhấn phím ESC sẽhiện menu   |
|                                   | > đểsave game, nút return đểthoát |
|                                   | > ra                              |
+===================================+===================================+
+-----------------------------------+-----------------------------------+

> ngoài\
> - dùng mũi tên đểđiều hướng, enter đểchọn\
> - nếu chọn save game thì sẽhiện ra dòng chữyour game has been saved.
>
> ![](vertopal_8a88c408b64841bc9473e6d0dfb0f645/media/image7.png){width="6.270833333333333in"
> height="4.926388888888889in"}
>
> **RESUME GAME**\
> Tiếp tục chơi game đã được lưu, thời gian bắt đầu từthời gian mà game
> sốgiâyđược lưu
>
> ![](vertopal_8a88c408b64841bc9473e6d0dfb0f645/media/image8.png){width="7.041665573053368in"
> height="5.280554461942257in"}
>
> **MÀN HÌNH THẮNG**\
> - hiện chữ"YOU WON"\
> - nếu đạt highscore cao nhất thì hiện "YOU REACHED NEW HIGHSCORE"
>
> ![](vertopal_8a88c408b64841bc9473e6d0dfb0f645/media/image9.png){width="6.270833333333333in"
> height="4.822221128608924in"}
>
> **MÀN HÌNH THUA**
>
> Hiện vịtrí tất cảnhững quảbom, vịtrí những lá cờđặt đúng và những lá
> cờđặt sai,, hiện chữ"YOU LOST"!, hiện menu gồm 2 phím New game (tạo
> game mới) và return
>
> ![](vertopal_8a88c408b64841bc9473e6d0dfb0f645/media/image10.png){width="6.270833333333333in"
> height="4.98888779527559in"}
>
> **HIGHSCORE**\
> Hiện top 3 thời gian nhanh nhất: first, second, third
>
> ![](vertopal_8a88c408b64841bc9473e6d0dfb0f645/media/image11.png){width="6.270832239720035in"
> height="3.125in"}
