Nhóm 12
Đề tài: Hệ thống Quản lý Giỏ hàng & Xử lý Đơn hàng Mini.
   Mô tả đề tài:đề tài là là "Xây dựng Hệ thống Quản lý Giỏ hàng và Hàng đợi Thanh toán" (Shopping Cart & Payment Queue Management System).
Mục tiêu của đề tài là giải quyết bài toán quản lý quy trình mua sắm của khách hàng qua 2 giai đoạn chính:
+Lựa chọn & Tích lũy hàng hóa (Quản lý giỏ hàng cá nhân).
+Xếp hàng & Thanh toán (Quản lý hàng đợi thanh toán chung).
Chương trình triển khai hệ thống quản lý giỏ hàng và hàng đợi thanh toán sử dụng các cấu trúc dữ liệu danh sách liên kết đơn (Singly Linked List) và hàng đợi (Queue).
Danh sách liên kết đơn (Singly Linked List)
Thành phần trong code: Class ShoppingCart (với các con trỏ ItemNode).
Có vai trò quản lý danh sách mặt hàng động trong giỏ. Cho phép thêm, sửa số lượng, xóa sản phẩm linh hoạt mà không bị giới hạn kích thước mảng.
Hàng đợi (Queue - FIFO)
Thành phần trong code: Class OrderQueue (với các con trỏ OrderNode).
Có vai trò quản lý danh sách các đơn hàng chờ thanh toán. Đảm bảo tính công bằng theo nguyên tắc "đến trước - xử lý trước" (First-In, First-Out).
Các chức năng nghiệp vụ chính:
1.	Thêm / Cộng dồn sản phẩm: Thêm sản phẩm mới vào giỏ hoặc tự động cộng dồn số lượng nếu sản phẩm đã có. 
2.	Cập nhật số lượng: Đổi số lượng mua của sản phẩm (xóa sản phẩm nếu nhập số lượng kém hơn hoặc bằng 0). 
3.	Xóa sản phẩm: Loại bỏ sản phẩm chỉ định ra khỏi giỏ hàng và giải phóng ô nhớ. 
4.	Xem chi tiết giỏ hàng: Duyệt danh sách liên kết, hiển thị thông tin sản phẩm và tính tổng giá trị giỏ hàng. 
5.	Chuyển giỏ hàng thành đơn hàng: Thực hiện sao chép sâu danh sách món hàng để tạo đơn hàng mới đẩy vào Queue, sau đó xóa sạch giỏ hàng. 
6.	Xem danh sách hàng đợi: Duyệt danh sách các đơn hàng đang chờ thanh toán từ đầu (front) tới cuối (rear). 
7.	Sắp xếp đơn hàng theo tổng tiền: Hoán đổi thông tin đơn hàng trong hàng đợi để ưu tiên các đơn hàng có giá trị cao. 
8.	Xử lý thanh toán đơn hàng (FIFO): Rút đơn hàng ở đầu hàng đợi, in hóa đơn chi tiết và giải phóng bộ nhớ động.
9.	Hướng dẫn Biên dịch & Chạy Chương trình bằng cách sử dụng Dev-C++ / Code::Blocks
Tải và cài đặt Dev-C++ hoặc Code::Blocks (bản có tích hợp sẵn trình biên dịch MinGW/GCC).
Mở file baitaplondsa.cpp.
Nhấn F11 (trong Dev-C++) để biên dịch và chạy trực tiếp chương trình.
