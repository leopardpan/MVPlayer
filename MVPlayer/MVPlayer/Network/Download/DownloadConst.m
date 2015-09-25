//
//  DownloadConst.m
//  MVPlayer
//
//  Created by 潘柏信 on 15/9/24.
//  Copyright (c) 2015年 leopard. All rights reserved.
//

#import "DownloadConst.h"

/******** 通知 Begin ********/
/** 下载进度发生改变的通知 */
NSString * const DownloadProgressDidChangeNotification = @"DownloadProgressDidChangeNotification";
/** 下载状态发生改变的通知 */
NSString * const DownloadStateDidChangeNotification = @"DownloadStateDidChangeNotification";
/** 利用这个key从通知中取出对应的DownloadInfo对象 */
NSString * const DownloadInfoKey = @"DownloadInfoKey";
/******** 通知 End ********/