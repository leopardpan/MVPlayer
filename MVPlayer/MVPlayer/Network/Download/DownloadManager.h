//
//  DownloadManager.h
//  MVPlayer
//
//  Created by 潘柏信 on 15/9/24.
//  Copyright (c) 2015年 leopard. All rights reserved.
//

#import <Foundation/Foundation.h>

@class DownloadInfo;

/****************** 数据类型 Begin ******************/
/** 下载状态 */
typedef NS_ENUM(NSInteger, DownloadState) {
    DownloadStateNone = 0,     // 闲置状态（除后面几种状态以外的其他状态）
    DownloadStateWillResume,   // 即将下载（等待下载）
    DownloadStateResumed,      // 下载中
    DownloadStateSuspened,     // 暂停中
    DownloadStateCompleted     // 已经完全下载完毕
} NS_ENUM_AVAILABLE_IOS(2_0);

/**
 *  跟踪下载进度的Block回调
 *
 *  @param bytesWritten              【这次回调】写入的数据量
 *  @param totalBytesWritten         【目前总共】写入的数据量
 *  @param totalBytesExpectedToWrite 【最终需要】写入的数据量
 */
typedef void (^DownloadProgressChangeBlock)(NSInteger bytesWritten, NSInteger totalBytesWritten, NSInteger totalBytesExpectedToWrite);

/**
 *  状态改变的Block回调
 *
 *  @param file 文件的下载路径
 *  @param error    失败的描述信息
 */
typedef void (^DownloadStateChangeBlock)(DownloadState state, NSString *file, NSError *error);
/****************** 数据类型 End ******************/


/****************** DownloadInfo Begin ******************/
/**
 *  下载的描述信息
 */
@interface DownloadInfo : NSObject
/** 下载状态 */
@property (assign, nonatomic, readonly) DownloadState state;
/** 这次写入的数量 */
@property (assign, nonatomic, readonly) NSInteger bytesWritten;
/** 已下载的数量 */
@property (assign, nonatomic, readonly) NSInteger totalBytesWritten;
/** 文件的总大小 */
@property (assign, nonatomic, readonly) NSInteger totalBytesExpectedToWrite;
/** 文件名 */
@property (copy, nonatomic, readonly) NSString *filename;
/** 文件路径 */
@property (copy, nonatomic, readonly) NSString *file;
/** 文件url */
@property (copy, nonatomic, readonly) NSString *url;
/** 下载的错误信息 */
@property (strong, nonatomic, readonly) NSError *error;
@end
/****************** DownloadInfo End ******************/


/****************** DownloadManager Begin ******************/
/**
 *  文件下载管理者，管理所有文件的下载操作
 *  - 管理文件下载操作
 *  - 获得文件下载操作
 */
@interface DownloadManager : NSObject
/** 回调的队列 */
@property (strong, nonatomic) NSOperationQueue *queue;
/** 最大同时下载数 */
@property (assign, nonatomic) int maxDownloadingCount;

+ (instancetype)defaultManager;
+ (instancetype)manager;
+ (instancetype)managerWithIdentifier:(NSString *)identifier;

/**
 *  全部文件取消下载(一旦被取消了，需要重新调用download方法)
 */
- (void)cancelAll;
/**
 *  全部文件取消下载(一旦被取消了，需要重新调用download方法)
 */
+ (void)cancelAll;

/**
 *  取消下载某个文件(一旦被取消了，需要重新调用download方法)
 */
- (void)cancel:(NSString *)url;

/**
 *  全部文件暂停下载
 */
- (void)suspendAll;
/**
 *  全部文件暂停下载
 */
+ (void)suspendAll;

/**
 *  暂停下载某个文件
 */
- (void)suspend:(NSString *)url;

/**
 * 全部文件开始\继续下载
 */
- (void)resumeAll;
/**
 * 全部文件开始\继续下载
 */
+ (void)resumeAll;

/**
 *  开始\继续下载某个文件
 */
- (void)resume:(NSString *)url;

/**
 *  获得某个文件的下载信息
 *
 *  @param url 文件的URL
 */
- (DownloadInfo *)downloadInfoForURL:(NSString *)url;

/**
 *  下载一个文件
 *
 *  @param url  文件的URL路径
 *
 *  @return YES代表文件已经下载完毕
 */
- (DownloadInfo *)download:(NSString *)url;

/**
 *  下载一个文件
 *
 *  @param url      文件的URL路径
 *  @param state    状态改变的回调
 *
 *  @return YES代表文件已经下载完毕
 */
- (DownloadInfo *)download:(NSString *)url state:(DownloadStateChangeBlock)state;

/**
 *  下载一个文件
 *
 *  @param url          文件的URL路径
 *  @param progress     下载进度的回调
 *  @param state        状态改变的回调
 *
 *  @return YES代表文件已经下载完毕
 */
- (DownloadInfo *)download:(NSString *)url progress:(DownloadProgressChangeBlock)progress state:(DownloadStateChangeBlock)state;

/**
 *  下载一个文件
 *
 *  @param url              文件的URL路径
 *  @param destinationPath  文件的存放路径
 *  @param progress         下载进度的回调
 *  @param state            状态改变的回调
 *
 *  @return YES代表文件已经下载完毕
 */
- (DownloadInfo *)download:(NSString *)url toDestinationPath:(NSString *)destinationPath progress:(DownloadProgressChangeBlock)progress state:(DownloadStateChangeBlock)state;
@end
/****************** DownloadManager End ******************/
