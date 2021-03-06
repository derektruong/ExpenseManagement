USE [master]
GO
/****** Object:  Database [DO_AN_THU_CHI]    Script Date: 22/11/2020 12:50:38 am ******/
CREATE DATABASE [DO_AN_THU_CHI]
 CONTAINMENT = NONE
 ON  PRIMARY 
( NAME = N'DO_AN_THU_CHI', FILENAME = N'F:\SQL_Server\SQL_2014\DO_AN_THU_CHI.mdf' , SIZE = 8192KB , MAXSIZE = UNLIMITED, FILEGROWTH = 65536KB )
 LOG ON 
( NAME = N'DO_AN_THU_CHI_log', FILENAME = N'F:\SQL_Server\SQL_2014\DO_AN_THU_CHI_log.ldf' , SIZE = 8192KB , MAXSIZE = 2048GB , FILEGROWTH = 65536KB )
GO
ALTER DATABASE [DO_AN_THU_CHI] SET COMPATIBILITY_LEVEL = 120
GO
IF (1 = FULLTEXTSERVICEPROPERTY('IsFullTextInstalled'))
begin
EXEC [DO_AN_THU_CHI].[dbo].[sp_fulltext_database] @action = 'enable'
end
GO
ALTER DATABASE [DO_AN_THU_CHI] SET ANSI_NULL_DEFAULT OFF 
GO
ALTER DATABASE [DO_AN_THU_CHI] SET ANSI_NULLS OFF 
GO
ALTER DATABASE [DO_AN_THU_CHI] SET ANSI_PADDING OFF 
GO
ALTER DATABASE [DO_AN_THU_CHI] SET ANSI_WARNINGS OFF 
GO
ALTER DATABASE [DO_AN_THU_CHI] SET ARITHABORT OFF 
GO
ALTER DATABASE [DO_AN_THU_CHI] SET AUTO_CLOSE ON 
GO
ALTER DATABASE [DO_AN_THU_CHI] SET AUTO_SHRINK OFF 
GO
ALTER DATABASE [DO_AN_THU_CHI] SET AUTO_UPDATE_STATISTICS ON 
GO
ALTER DATABASE [DO_AN_THU_CHI] SET CURSOR_CLOSE_ON_COMMIT OFF 
GO
ALTER DATABASE [DO_AN_THU_CHI] SET CURSOR_DEFAULT  GLOBAL 
GO
ALTER DATABASE [DO_AN_THU_CHI] SET CONCAT_NULL_YIELDS_NULL OFF 
GO
ALTER DATABASE [DO_AN_THU_CHI] SET NUMERIC_ROUNDABORT OFF 
GO
ALTER DATABASE [DO_AN_THU_CHI] SET QUOTED_IDENTIFIER OFF 
GO
ALTER DATABASE [DO_AN_THU_CHI] SET RECURSIVE_TRIGGERS OFF 
GO
ALTER DATABASE [DO_AN_THU_CHI] SET  DISABLE_BROKER 
GO
ALTER DATABASE [DO_AN_THU_CHI] SET AUTO_UPDATE_STATISTICS_ASYNC OFF 
GO
ALTER DATABASE [DO_AN_THU_CHI] SET DATE_CORRELATION_OPTIMIZATION OFF 
GO
ALTER DATABASE [DO_AN_THU_CHI] SET TRUSTWORTHY OFF 
GO
ALTER DATABASE [DO_AN_THU_CHI] SET ALLOW_SNAPSHOT_ISOLATION OFF 
GO
ALTER DATABASE [DO_AN_THU_CHI] SET PARAMETERIZATION SIMPLE 
GO
ALTER DATABASE [DO_AN_THU_CHI] SET READ_COMMITTED_SNAPSHOT OFF 
GO
ALTER DATABASE [DO_AN_THU_CHI] SET HONOR_BROKER_PRIORITY OFF 
GO
ALTER DATABASE [DO_AN_THU_CHI] SET RECOVERY FULL 
GO
ALTER DATABASE [DO_AN_THU_CHI] SET  MULTI_USER 
GO
ALTER DATABASE [DO_AN_THU_CHI] SET PAGE_VERIFY CHECKSUM  
GO
ALTER DATABASE [DO_AN_THU_CHI] SET DB_CHAINING OFF 
GO
ALTER DATABASE [DO_AN_THU_CHI] SET FILESTREAM( NON_TRANSACTED_ACCESS = OFF ) 
GO
ALTER DATABASE [DO_AN_THU_CHI] SET TARGET_RECOVERY_TIME = 60 SECONDS 
GO
ALTER DATABASE [DO_AN_THU_CHI] SET DELAYED_DURABILITY = DISABLED 
GO
USE [DO_AN_THU_CHI]
GO
/****** Object:  Table [dbo].[DanhMucChiTieu]    Script Date: 22/11/2020 12:50:38 am ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[DanhMucChiTieu](
	[MaDanhMuc] [varchar](100) NOT NULL,
	[TenDanhMuc] [nvarchar](100) NOT NULL,
	[TongTien] [bigint] NULL,
	[MoTa] [ntext] NULL,
	[TenChu] [varchar](50) NULL,
	[ID_DanhMuc] [int] IDENTITY(1,1) NOT NULL,
PRIMARY KEY CLUSTERED 
(
	[ID_DanhMuc] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY] TEXTIMAGE_ON [PRIMARY]
GO
/****** Object:  Table [dbo].[KhoanChi]    Script Date: 22/11/2020 12:50:38 am ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[KhoanChi](
	[MaKhoanChi] [int] IDENTITY(1,1) NOT NULL,
	[SoTien] [bigint] NULL,
	[NgayChiTieu] [date] NULL,
	[GhiChu] [ntext] NULL,
	[TenTaiKhoan] [nvarchar](50) NULL,
	[ID_DanhMuc] [int] NULL,
PRIMARY KEY CLUSTERED 
(
	[MaKhoanChi] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY] TEXTIMAGE_ON [PRIMARY]
GO
/****** Object:  Table [dbo].[LoaiThuNhap]    Script Date: 22/11/2020 12:50:38 am ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[LoaiThuNhap](
	[MaLoaiThuNhap] [int] IDENTITY(1,1) NOT NULL,
	[LoaiThuNhap] [nvarchar](50) NOT NULL,
	[GhiChu] [ntext] NULL,
	[TenChu] [varchar](50) NULL,
PRIMARY KEY CLUSTERED 
(
	[MaLoaiThuNhap] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY] TEXTIMAGE_ON [PRIMARY]
GO
/****** Object:  Table [dbo].[Loan]    Script Date: 22/11/2020 12:50:38 am ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[Loan](
	[MaNo] [int] IDENTITY(1,1) NOT NULL,
	[TenNo] [nvarchar](50) NOT NULL,
	[KyHan] [date] NULL,
	[MaTaiKhoan] [int] NOT NULL,
PRIMARY KEY CLUSTERED 
(
	[MaNo] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY]
GO
/****** Object:  Table [dbo].[NguoiDung]    Script Date: 22/11/2020 12:50:38 am ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[NguoiDung](
	[TenDangNhap] [varchar](50) NOT NULL,
	[MaPin] [varchar](300) NULL,
	[HoVaTen] [nvarchar](50) NULL,
	[Email] [varchar](30) NULL,
	[CongViec] [nvarchar](50) NULL,
PRIMARY KEY CLUSTERED 
(
	[TenDangNhap] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY]
GO
/****** Object:  Table [dbo].[TaiKhoan]    Script Date: 22/11/2020 12:50:38 am ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[TaiKhoan](
	[MaTaiKhoan] [int] IDENTITY(1,1) NOT NULL,
	[Loai] [nvarchar](50) NULL,
	[Ten] [nvarchar](50) NOT NULL,
	[SoDu] [bigint] NULL,
	[BaoGomTrongTongSoDu] [int] NULL,
	[TenChu] [varchar](50) NULL,
	[MoTa] [ntext] NULL,
PRIMARY KEY CLUSTERED 
(
	[MaTaiKhoan] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY] TEXTIMAGE_ON [PRIMARY]
GO
/****** Object:  Table [dbo].[ThongKe]    Script Date: 22/11/2020 12:50:38 am ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[ThongKe](
	[MaThongKe] [int] IDENTITY(1,1) NOT NULL,
	[ThoiGian] [date] NULL,
	[TenChu] [varchar](50) NOT NULL,
	[MaThuNhap] [int] NULL,
	[MaKhoanChi] [int] NULL,
PRIMARY KEY CLUSTERED 
(
	[MaThongKe] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY]
GO
/****** Object:  Table [dbo].[ThuNhap]    Script Date: 22/11/2020 12:50:38 am ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[ThuNhap](
	[MaThuNhap] [int] IDENTITY(1,1) NOT NULL,
	[SoTien] [bigint] NULL,
	[GhiChu] [ntext] NULL,
	[TenTaiKhoan] [nvarchar](50) NOT NULL,
	[NgayThuNhap] [date] NULL,
	[MaLoaiThuNhap] [int] NULL,
PRIMARY KEY CLUSTERED 
(
	[MaThuNhap] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY] TEXTIMAGE_ON [PRIMARY]
GO
/****** Object:  Table [dbo].[TietKiem]    Script Date: 22/11/2020 12:50:38 am ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[TietKiem](
	[MaTietKiem] [int] IDENTITY(1,1) NOT NULL,
	[TenTietKiem] [nvarchar](50) NOT NULL,
	[MucTieu] [bigint] NULL,
	[MaTaiKhoan] [int] NOT NULL,
PRIMARY KEY CLUSTERED 
(
	[MaTietKiem] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY]
GO
SET IDENTITY_INSERT [dbo].[DanhMucChiTieu] ON 

INSERT [dbo].[DanhMucChiTieu] ([MaDanhMuc], [TenDanhMuc], [TongTien], [MoTa], [TenChu], [ID_DanhMuc]) VALUES (N'BH', N'Bách Hoá', 125000, N'Đồ gia dụng, đồ chơi, đồ gia dụng,...', N'user', 56)
INSERT [dbo].[DanhMucChiTieu] ([MaDanhMuc], [TenDanhMuc], [TongTien], [MoTa], [TenChu], [ID_DanhMuc]) VALUES (N'DC', N'Di Chuyển', 0, N'Xăng, vé xe,...', N'user', 57)
INSERT [dbo].[DanhMucChiTieu] ([MaDanhMuc], [TenDanhMuc], [TongTien], [MoTa], [TenChu], [ID_DanhMuc]) VALUES (N'GD', N'Gia Đình', 0, N'Chi phí gia đình, nội thất,...', N'user', 58)
INSERT [dbo].[DanhMucChiTieu] ([MaDanhMuc], [TenDanhMuc], [TongTien], [MoTa], [TenChu], [ID_DanhMuc]) VALUES (N'GT', N'Giải Trí', 0, N'Xem phim, du lịch,...', N'user', 59)
INSERT [dbo].[DanhMucChiTieu] ([MaDanhMuc], [TenDanhMuc], [TongTien], [MoTa], [TenChu], [ID_DanhMuc]) VALUES (N'HD', N'Hoá Đơn', 0, N'Hoá đơn điện, nước, internet, cáp truyền hình,...', N'user', 60)
INSERT [dbo].[DanhMucChiTieu] ([MaDanhMuc], [TenDanhMuc], [TongTien], [MoTa], [TenChu], [ID_DanhMuc]) VALUES (N'HP', N'Học Phí', 505000, N'Học phí', N'user', 61)
INSERT [dbo].[DanhMucChiTieu] ([MaDanhMuc], [TenDanhMuc], [TongTien], [MoTa], [TenChu], [ID_DanhMuc]) VALUES (N'KD', N'Kinh Doanh', 0, N'Chi phí kinh tế', N'user', 62)
INSERT [dbo].[DanhMucChiTieu] ([MaDanhMuc], [TenDanhMuc], [TongTien], [MoTa], [TenChu], [ID_DanhMuc]) VALUES (N'MS', N'Mua Sắm', 675000, N'Quần áo, phụ kiện, mỹ phẩm,...', N'user', 63)
INSERT [dbo].[DanhMucChiTieu] ([MaDanhMuc], [TenDanhMuc], [TongTien], [MoTa], [TenChu], [ID_DanhMuc]) VALUES (N'OT', N'Khác', 0, N'Mục khác,...', N'user', 64)
INSERT [dbo].[DanhMucChiTieu] ([MaDanhMuc], [TenDanhMuc], [TongTien], [MoTa], [TenChu], [ID_DanhMuc]) VALUES (N'QT', N'Quà Tặng', 0, N'Quà tặng,...', N'user', 65)
INSERT [dbo].[DanhMucChiTieu] ([MaDanhMuc], [TenDanhMuc], [TongTien], [MoTa], [TenChu], [ID_DanhMuc]) VALUES (N'SK', N'Sức Khoẻ', 0, N'Thuốc, dược phẩm,...', N'user', 66)
SET IDENTITY_INSERT [dbo].[DanhMucChiTieu] OFF
GO
SET IDENTITY_INSERT [dbo].[KhoanChi] ON 

INSERT [dbo].[KhoanChi] ([MaKhoanChi], [SoTien], [NgayChiTieu], [GhiChu], [TenTaiKhoan], [ID_DanhMuc]) VALUES (63, 125000, CAST(N'2020-10-22' AS Date), N'Rau', N'Thẻ BIDV', 56)
INSERT [dbo].[KhoanChi] ([MaKhoanChi], [SoTien], [NgayChiTieu], [GhiChu], [TenTaiKhoan], [ID_DanhMuc]) VALUES (64, 625000, CAST(N'2020-10-23' AS Date), N'Quần tây', N'Tiết kiệm 1', 63)
INSERT [dbo].[KhoanChi] ([MaKhoanChi], [SoTien], [NgayChiTieu], [GhiChu], [TenTaiKhoan], [ID_DanhMuc]) VALUES (65, 50000, CAST(N'2020-10-23' AS Date), N'Áo thun', N'Thẻ BIDV', 63)
INSERT [dbo].[KhoanChi] ([MaKhoanChi], [SoTien], [NgayChiTieu], [GhiChu], [TenTaiKhoan], [ID_DanhMuc]) VALUES (66, 505000, CAST(N'2020-11-18' AS Date), N'Học C++ online', N'Tiết kiệm 1', 61)
SET IDENTITY_INSERT [dbo].[KhoanChi] OFF
GO
SET IDENTITY_INSERT [dbo].[LoaiThuNhap] ON 

INSERT [dbo].[LoaiThuNhap] ([MaLoaiThuNhap], [LoaiThuNhap], [GhiChu], [TenChu]) VALUES (16, N'Lương', N'test', N'user')
INSERT [dbo].[LoaiThuNhap] ([MaLoaiThuNhap], [LoaiThuNhap], [GhiChu], [TenChu]) VALUES (17, N'Quà tặng', N'Gift', N'user')
SET IDENTITY_INSERT [dbo].[LoaiThuNhap] OFF
GO
INSERT [dbo].[NguoiDung] ([TenDangNhap], [MaPin], [HoVaTen], [Email], [CongViec]) VALUES (N'user', N'2021?', N'Trương Minh Đức', N'minhduc0589@gmail.com', N'Sinh viên')
GO
SET IDENTITY_INSERT [dbo].[TaiKhoan] ON 

INSERT [dbo].[TaiKhoan] ([MaTaiKhoan], [Loai], [Ten], [SoDu], [BaoGomTrongTongSoDu], [TenChu], [MoTa]) VALUES (48, N'Thường xuyên(Thẻ, tiền mặt,...)', N'Thẻ BIDV', 57663000, 1, N'user', N'up1')
INSERT [dbo].[TaiKhoan] ([MaTaiKhoan], [Loai], [Ten], [SoDu], [BaoGomTrongTongSoDu], [TenChu], [MoTa]) VALUES (49, N'Tiết kiệm', N'Tiết kiệm 1', 24970000, 1, N'user', N'Tích mua mac')
SET IDENTITY_INSERT [dbo].[TaiKhoan] OFF
GO
SET IDENTITY_INSERT [dbo].[ThongKe] ON 

INSERT [dbo].[ThongKe] ([MaThongKe], [ThoiGian], [TenChu], [MaThuNhap], [MaKhoanChi]) VALUES (30, CAST(N'2020-10-22' AS Date), N'user', 39, NULL)
INSERT [dbo].[ThongKe] ([MaThongKe], [ThoiGian], [TenChu], [MaThuNhap], [MaKhoanChi]) VALUES (32, CAST(N'2020-10-22' AS Date), N'user', NULL, 63)
INSERT [dbo].[ThongKe] ([MaThongKe], [ThoiGian], [TenChu], [MaThuNhap], [MaKhoanChi]) VALUES (33, CAST(N'2020-10-23' AS Date), N'user', NULL, 64)
INSERT [dbo].[ThongKe] ([MaThongKe], [ThoiGian], [TenChu], [MaThuNhap], [MaKhoanChi]) VALUES (34, CAST(N'2020-10-23' AS Date), N'user', NULL, 65)
INSERT [dbo].[ThongKe] ([MaThongKe], [ThoiGian], [TenChu], [MaThuNhap], [MaKhoanChi]) VALUES (35, CAST(N'2020-10-23' AS Date), N'user', 40, NULL)
INSERT [dbo].[ThongKe] ([MaThongKe], [ThoiGian], [TenChu], [MaThuNhap], [MaKhoanChi]) VALUES (36, CAST(N'2020-10-23' AS Date), N'user', 41, NULL)
INSERT [dbo].[ThongKe] ([MaThongKe], [ThoiGian], [TenChu], [MaThuNhap], [MaKhoanChi]) VALUES (37, CAST(N'2020-10-23' AS Date), N'user', 42, NULL)
INSERT [dbo].[ThongKe] ([MaThongKe], [ThoiGian], [TenChu], [MaThuNhap], [MaKhoanChi]) VALUES (38, CAST(N'2020-10-23' AS Date), N'user', 43, NULL)
INSERT [dbo].[ThongKe] ([MaThongKe], [ThoiGian], [TenChu], [MaThuNhap], [MaKhoanChi]) VALUES (42, CAST(N'2020-11-17' AS Date), N'user', 47, NULL)
INSERT [dbo].[ThongKe] ([MaThongKe], [ThoiGian], [TenChu], [MaThuNhap], [MaKhoanChi]) VALUES (43, CAST(N'2020-11-18' AS Date), N'user', NULL, 66)
SET IDENTITY_INSERT [dbo].[ThongKe] OFF
GO
SET IDENTITY_INSERT [dbo].[ThuNhap] ON 

INSERT [dbo].[ThuNhap] ([MaThuNhap], [SoTien], [GhiChu], [TenTaiKhoan], [NgayThuNhap], [MaLoaiThuNhap]) VALUES (39, 100000, N'test', N'Thẻ BIDV', CAST(N'2020-10-22' AS Date), 16)
INSERT [dbo].[ThuNhap] ([MaThuNhap], [SoTien], [GhiChu], [TenTaiKhoan], [NgayThuNhap], [MaLoaiThuNhap]) VALUES (40, 267000, N'lương lậu', N'Thẻ BIDV', CAST(N'2020-10-23' AS Date), 16)
INSERT [dbo].[ThuNhap] ([MaThuNhap], [SoTien], [GhiChu], [TenTaiKhoan], [NgayThuNhap], [MaLoaiThuNhap]) VALUES (41, 500000, N'quà', N'Tiết kiệm 1', CAST(N'2020-10-23' AS Date), 16)
INSERT [dbo].[ThuNhap] ([MaThuNhap], [SoTien], [GhiChu], [TenTaiKhoan], [NgayThuNhap], [MaLoaiThuNhap]) VALUES (42, 24500000, N'quà', N'Tiết kiệm 1', CAST(N'2020-10-23' AS Date), 16)
INSERT [dbo].[ThuNhap] ([MaThuNhap], [SoTien], [GhiChu], [TenTaiKhoan], [NgayThuNhap], [MaLoaiThuNhap]) VALUES (43, 50000, N'test', N'Tiết kiệm 1', CAST(N'2020-10-23' AS Date), 16)
INSERT [dbo].[ThuNhap] ([MaThuNhap], [SoTien], [GhiChu], [TenTaiKhoan], [NgayThuNhap], [MaLoaiThuNhap]) VALUES (47, 560000, N'test', N'Thẻ BIDV', CAST(N'2020-11-17' AS Date), 17)
SET IDENTITY_INSERT [dbo].[ThuNhap] OFF
GO
SET IDENTITY_INSERT [dbo].[TietKiem] ON 

INSERT [dbo].[TietKiem] ([MaTietKiem], [TenTietKiem], [MucTieu], [MaTaiKhoan]) VALUES (8, N'Tiết kiệm 1', 50000000, 49)
SET IDENTITY_INSERT [dbo].[TietKiem] OFF
GO
SET ANSI_PADDING ON
GO
/****** Object:  Index [user_index]    Script Date: 22/11/2020 12:50:38 am ******/
CREATE UNIQUE NONCLUSTERED INDEX [user_index] ON [dbo].[LoaiThuNhap]
(
	[LoaiThuNhap] ASC
)
WHERE ([TenChu]='user')
WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, SORT_IN_TEMPDB = OFF, IGNORE_DUP_KEY = OFF, DROP_EXISTING = OFF, ONLINE = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
GO
SET ANSI_PADDING ON
GO
/****** Object:  Index [UQ__Loan__4CF9B44F20C44E35]    Script Date: 22/11/2020 12:50:38 am ******/
ALTER TABLE [dbo].[Loan] ADD UNIQUE NONCLUSTERED 
(
	[TenNo] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, SORT_IN_TEMPDB = OFF, IGNORE_DUP_KEY = OFF, ONLINE = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
GO
SET ANSI_PADDING ON
GO
/****** Object:  Index [user_index]    Script Date: 22/11/2020 12:50:38 am ******/
CREATE UNIQUE NONCLUSTERED INDEX [user_index] ON [dbo].[TaiKhoan]
(
	[Ten] ASC
)
WHERE ([TenChu]='user')
WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, SORT_IN_TEMPDB = OFF, IGNORE_DUP_KEY = OFF, DROP_EXISTING = OFF, ONLINE = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
GO
SET ANSI_PADDING ON
GO
/****** Object:  Index [UQ__TietKiem__E6EB881FAEFA5BAC]    Script Date: 22/11/2020 12:50:38 am ******/
ALTER TABLE [dbo].[TietKiem] ADD UNIQUE NONCLUSTERED 
(
	[TenTietKiem] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, SORT_IN_TEMPDB = OFF, IGNORE_DUP_KEY = OFF, ONLINE = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
GO
ALTER TABLE [dbo].[DanhMucChiTieu] ADD  DEFAULT (N'Mô tả') FOR [MoTa]
GO
ALTER TABLE [dbo].[KhoanChi] ADD  DEFAULT (N'Ghi chú') FOR [GhiChu]
GO
ALTER TABLE [dbo].[DanhMucChiTieu]  WITH CHECK ADD FOREIGN KEY([TenChu])
REFERENCES [dbo].[NguoiDung] ([TenDangNhap])
GO
ALTER TABLE [dbo].[KhoanChi]  WITH CHECK ADD  CONSTRAINT [FK_ID_DanhMuc_KhoanChi] FOREIGN KEY([ID_DanhMuc])
REFERENCES [dbo].[DanhMucChiTieu] ([ID_DanhMuc])
GO
ALTER TABLE [dbo].[KhoanChi] CHECK CONSTRAINT [FK_ID_DanhMuc_KhoanChi]
GO
ALTER TABLE [dbo].[LoaiThuNhap]  WITH CHECK ADD  CONSTRAINT [FK_TenChuLTN] FOREIGN KEY([TenChu])
REFERENCES [dbo].[NguoiDung] ([TenDangNhap])
GO
ALTER TABLE [dbo].[LoaiThuNhap] CHECK CONSTRAINT [FK_TenChuLTN]
GO
ALTER TABLE [dbo].[Loan]  WITH CHECK ADD  CONSTRAINT [FK_MaTaiKhoan_Loan] FOREIGN KEY([MaTaiKhoan])
REFERENCES [dbo].[TaiKhoan] ([MaTaiKhoan])
GO
ALTER TABLE [dbo].[Loan] CHECK CONSTRAINT [FK_MaTaiKhoan_Loan]
GO
ALTER TABLE [dbo].[TaiKhoan]  WITH CHECK ADD  CONSTRAINT [FK_HG1_TenDangNhap] FOREIGN KEY([TenChu])
REFERENCES [dbo].[NguoiDung] ([TenDangNhap])
GO
ALTER TABLE [dbo].[TaiKhoan] CHECK CONSTRAINT [FK_HG1_TenDangNhap]
GO
ALTER TABLE [dbo].[ThongKe]  WITH CHECK ADD  CONSTRAINT [FK_MaKhoanChi_KhoanChi] FOREIGN KEY([MaKhoanChi])
REFERENCES [dbo].[KhoanChi] ([MaKhoanChi])
GO
ALTER TABLE [dbo].[ThongKe] CHECK CONSTRAINT [FK_MaKhoanChi_KhoanChi]
GO
ALTER TABLE [dbo].[ThongKe]  WITH CHECK ADD  CONSTRAINT [FK_MaThuNhap_ThuNhap] FOREIGN KEY([MaThuNhap])
REFERENCES [dbo].[ThuNhap] ([MaThuNhap])
GO
ALTER TABLE [dbo].[ThongKe] CHECK CONSTRAINT [FK_MaThuNhap_ThuNhap]
GO
ALTER TABLE [dbo].[ThongKe]  WITH CHECK ADD  CONSTRAINT [FK_TenChu_ThongKe] FOREIGN KEY([TenChu])
REFERENCES [dbo].[NguoiDung] ([TenDangNhap])
GO
ALTER TABLE [dbo].[ThongKe] CHECK CONSTRAINT [FK_TenChu_ThongKe]
GO
ALTER TABLE [dbo].[ThuNhap]  WITH CHECK ADD  CONSTRAINT [FK_MaLoaiThuNhap_ThuNhap] FOREIGN KEY([MaLoaiThuNhap])
REFERENCES [dbo].[LoaiThuNhap] ([MaLoaiThuNhap])
GO
ALTER TABLE [dbo].[ThuNhap] CHECK CONSTRAINT [FK_MaLoaiThuNhap_ThuNhap]
GO
ALTER TABLE [dbo].[TietKiem]  WITH CHECK ADD  CONSTRAINT [FK_MaTaiKhoan] FOREIGN KEY([MaTaiKhoan])
REFERENCES [dbo].[TaiKhoan] ([MaTaiKhoan])
GO
ALTER TABLE [dbo].[TietKiem] CHECK CONSTRAINT [FK_MaTaiKhoan]
GO
/****** Object:  Trigger [dbo].[TRG_ThemChiTieu]    Script Date: 22/11/2020 12:50:38 am ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TRIGGER [dbo].[TRG_ThemChiTieu]
ON [dbo].[KhoanChi]
FOR INSERT
AS
BEGIN
	DECLARE @VAR_MaKhoanChi int; --Lấy mã khoản chi sau insert
	DECLARE @ID_DanhMuc int;
	DECLARE @VAR_NgayChiTieu date;
	DECLARE @VAR_TenChu varchar(50);
	DECLARE @VAR_TenTaiKhoan nvarchar(50);
	DECLARE @VAR_SoTienChi bigint;
	DECLARE @VAR_SoTienCon bigint;
	SELECT @VAR_MaKhoanChi = kc.MaKhoanChi, @VAR_NgayChiTieu = kc.NgayChiTieu, @VAR_TenChu = dmct.TenChu, @VAR_SoTienChi = kc.SoTien, @VAR_TenTaiKhoan = kc.TenTaiKhoan, @ID_DanhMuc = kc.ID_DanhMuc
		FROM INSERTED kc JOIN DanhMucChiTieu dmct 
			ON kc.ID_DanhMuc = dmct.ID_DanhMuc
	
	SELECT @VAR_SoTienCon = tk.SoDu FROM TaiKhoan tk WHERE 	tk.TenChu = @VAR_TenChu AND tk.Ten = @VAR_TenTaiKhoan

	IF @VAR_SoTienCon < @VAR_SoTienChi
		BEGIN
			ROLLBACK TRANSACTION
		END
	ELSE
		BEGIN
			--Insert to ThongKe
			INSERT INTO dbo.ThongKe
			(
				--MaThongKe - column value is auto-generated
				ThoiGian,
				TenChu,
				MaThuNhap,
				MaKhoanChi
			)
			VALUES
			(
				-- MaThongKe - int
				@VAR_NgayChiTieu, -- ThoiGian - date
				@VAR_TenChu, -- TenChu - varchar
				NULL, -- MaThuNhap - int
				@VAR_MaKhoanChi -- MaKhoanChi - int
			)
			--Update bảng DanhMucChiTieu
			UPDATE DanhMucChiTieu
				SET	DanhMucChiTieu.TongTien = DanhMucChiTieu.TongTien + @VAR_SoTienChi
					WHERE DanhMucChiTieu.ID_DanhMuc = @ID_DanhMuc
			--Trừ tiền trong TaiKhoan
			UPDATE TaiKhoan
				SET TaiKhoan.SoDu = TaiKhoan.SoDu - @VAR_SoTienChi
					WHERE TaiKhoan.TenChu = @VAR_TenChu AND TaiKhoan.Ten = @VAR_TenTaiKhoan      
		END 
	
END
GO
ALTER TABLE [dbo].[KhoanChi] ENABLE TRIGGER [TRG_ThemChiTieu]
GO
/****** Object:  Trigger [dbo].[TRG_ThemThuNhap]    Script Date: 22/11/2020 12:50:38 am ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TRIGGER [dbo].[TRG_ThemThuNhap]
ON [dbo].[ThuNhap]
FOR INSERT
AS
BEGIN
	DECLARE @VAR_MaThuNhap int;	--Lấy mã thu nhập sau insert
	DECLARE @VAR_NgayThuNhap date;
	DECLARE @VAR_TenChu varchar(50);
	DECLARE @VAR_TenTaiKhoan nvarchar(50);
	DECLARE @VAR_SoTienThu bigint;
	DECLARE @VAR_LoaiTaiKhoan nvarchar(50);
	SELECT @VAR_MaThuNhap = tn.MaThuNhap, @VAR_NgayThuNhap = tn.NgayThuNhap, @VAR_TenChu = ltn.TenChu, @VAR_TenTaiKhoan = tn.TenTaiKhoan, @VAR_SoTienThu = tn.SoTien 
		FROM INSERTED tn JOIN LoaiThuNhap ltn 
			ON tn.MaLoaiThuNhap = ltn.MaLoaiThuNhap

	--Insert to ThongKe
	INSERT INTO dbo.ThongKe
	(
	    --MaThongKe - column value is auto-generated
	    ThoiGian,
	    TenChu,
	    MaThuNhap,
	    MaKhoanChi
	)
	VALUES
	(
	    -- MaThongKe - int
	    @VAR_NgayThuNhap, -- ThoiGian - date
	    @VAR_TenChu, -- TenChu - varchar
	    @VAR_MaThuNhap, -- MaThuNhap - int
	    NULL -- MaKhoanChi - int
	)
	--Update TaiKhoan
	SELECT @VAR_LoaiTaiKhoan = Loai FROM TaiKhoan WHERE TenChu = @VAR_TenChu AND Ten = @VAR_TenTaiKhoan  
	IF @VAR_LoaiTaiKhoan = N'Nợ'
		BEGIN
			UPDATE TaiKhoan
				SET TaiKhoan.SoDu = TaiKhoan.SoDu - @VAR_SoTienThu
					WHERE TaiKhoan.TenChu = @VAR_TenChu AND TaiKhoan.Ten = @VAR_TenTaiKhoan
		END
	ELSE
		BEGIN
			 UPDATE TaiKhoan
				SET TaiKhoan.SoDu = TaiKhoan.SoDu + @VAR_SoTienThu
					WHERE TaiKhoan.TenChu = @VAR_TenChu AND TaiKhoan.Ten = @VAR_TenTaiKhoan
		END 
END
GO
ALTER TABLE [dbo].[ThuNhap] ENABLE TRIGGER [TRG_ThemThuNhap]
GO
USE [master]
GO
ALTER DATABASE [DO_AN_THU_CHI] SET  READ_WRITE 
GO
