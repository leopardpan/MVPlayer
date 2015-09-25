//
//  DownloadConst.h
//  MVPlayer
//
//  Created by 潘柏信 on 15/9/24.
//  Copyright (c) 2015年 leopard. All rights reserved.
//

#import <Foundation/Foundation.h>

/******** 通知 Begin ********/
/** 下载进度发生改变的通知 */
extern NSString * const DownloadProgressDidChangeNotification;
/** 下载状态发生改变的通知 */
extern NSString * const DownloadStateDidChangeNotification;
/** 利用这个key从通知中取出对应的DownloadInfo对象 */
extern NSString * const DownloadInfoKey;

#define DownloadNoteCenter [NSNotificationCenter defaultCenter]
/******** 通知 End ********/