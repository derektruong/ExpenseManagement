USE [master]
GO
/****** Object:  Database [DO_AN_THU_CHI]    Script Date: 21/10/2020 11:57:09 am ******/
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
/****** Object:  Table [dbo].[DanhMucChiTieu]    Script Date: 21/10/2020 11:57:09 am ******/
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
/****** Object:  Table [dbo].[KhoanChi]    Script Date: 21/10/2020 11:57:09 am ******/
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
/****** Object:  Table [dbo].[LoaiThuNhap]    Script Date: 21/10/2020 11:57:09 am ******/
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
/****** Object:  Table [dbo].[Loan]    Script Date: 21/10/2020 11:57:09 am ******/
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
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY],
UNIQUE NONCLUSTERED 
(
	[TenNo] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY]
GO
/****** Object:  Table [dbo].[NguoiDung]    Script Date: 21/10/2020 11:57:09 am ******/
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
/****** Object:  Table [dbo].[TaiKhoan]    Script Date: 21/10/2020 11:57:09 am ******/
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
/****** Object:  Table [dbo].[ThongKe]    Script Date: 21/10/2020 11:57:09 am ******/
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
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY],
 CONSTRAINT [unique_ThoiGian] UNIQUE NONCLUSTERED 
(
	[ThoiGian] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY]
GO
/****** Object:  Table [dbo].[ThuNhap]    Script Date: 21/10/2020 11:57:09 am ******/
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
/****** Object:  Table [dbo].[TietKiem]    Script Date: 21/10/2020 11:57:09 am ******/
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
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY],
UNIQUE NONCLUSTERED 
(
	[TenTietKiem] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY]
GO
SET ANSI_PADDING ON
GO
/****** Object:  Index [derek_index]    Script Date: 21/10/2020 11:57:09 am ******/
CREATE UNIQUE NONCLUSTERED INDEX [derek_index] ON [dbo].[LoaiThuNhap]
(
	[LoaiThuNhap] ASC
)
WHERE ([TenChu]='derek')
WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, SORT_IN_TEMPDB = OFF, IGNORE_DUP_KEY = OFF, DROP_EXISTING = OFF, ONLINE = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
GO
SET ANSI_PADDING ON
GO
/****** Object:  Index [user_index]    Script Date: 21/10/2020 11:57:09 am ******/
CREATE UNIQUE NONCLUSTERED INDEX [user_index] ON [dbo].[LoaiThuNhap]
(
	[LoaiThuNhap] ASC
)
WHERE ([TenChu]='user')
WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, SORT_IN_TEMPDB = OFF, IGNORE_DUP_KEY = OFF, DROP_EXISTING = OFF, ONLINE = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
GO
SET ANSI_PADDING ON
GO
/****** Object:  Index [uservip_index]    Script Date: 21/10/2020 11:57:09 am ******/
CREATE UNIQUE NONCLUSTERED INDEX [uservip_index] ON [dbo].[LoaiThuNhap]
(
	[LoaiThuNhap] ASC
)
WHERE ([TenChu]='uservip')
WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, SORT_IN_TEMPDB = OFF, IGNORE_DUP_KEY = OFF, DROP_EXISTING = OFF, ONLINE = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
GO
SET ANSI_PADDING ON
GO
/****** Object:  Index [derek_index]    Script Date: 21/10/2020 11:57:09 am ******/
CREATE UNIQUE NONCLUSTERED INDEX [derek_index] ON [dbo].[TaiKhoan]
(
	[Ten] ASC
)
WHERE ([TenChu]='derek')
WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, SORT_IN_TEMPDB = OFF, IGNORE_DUP_KEY = OFF, DROP_EXISTING = OFF, ONLINE = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
GO
SET ANSI_PADDING ON
GO
/****** Object:  Index [user_index]    Script Date: 21/10/2020 11:57:09 am ******/
CREATE UNIQUE NONCLUSTERED INDEX [user_index] ON [dbo].[TaiKhoan]
(
	[Ten] ASC
)
WHERE ([TenChu]='user')
WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, SORT_IN_TEMPDB = OFF, IGNORE_DUP_KEY = OFF, DROP_EXISTING = OFF, ONLINE = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
GO
SET ANSI_PADDING ON
GO
/****** Object:  Index [uservip_index]    Script Date: 21/10/2020 11:57:09 am ******/
CREATE UNIQUE NONCLUSTERED INDEX [uservip_index] ON [dbo].[TaiKhoan]
(
	[Ten] ASC
)
WHERE ([TenChu]='uservip')
WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, SORT_IN_TEMPDB = OFF, IGNORE_DUP_KEY = OFF, DROP_EXISTING = OFF, ONLINE = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
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
USE [master]
GO
ALTER DATABASE [DO_AN_THU_CHI] SET  READ_WRITE 
GO
