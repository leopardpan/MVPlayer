//
//  TableVewCell.m
//  MVPlayer
//
//  Created by 潘柏信 on 15/9/24.
//  Copyright (c) 2015年 leopard. All rights reserved.
//

#import "TableViewCell.h"
#import "Download.h"
#import "ProgressView.h"
#import "DownloadManager.h"
#import <MediaPlayer/MediaPlayer.h>

@interface TableViewCell()
@property (weak, nonatomic) IBOutlet ProgressView *progressView;
@property (weak, nonatomic) IBOutlet UIButton *openButton;
@property (weak, nonatomic) IBOutlet UIButton *downloadButton;
@end

@implementation TableViewCell

- (void)setUrl:(NSString *)url
{
    _url = [url copy];
    
    // 设置文字
    self.textLabel.text = [url lastPathComponent];
    
    // 控制状态
    DownloadInfo *info = [[DownloadManager defaultManager] downloadInfoForURL:url];
    
    if (info.state == DownloadStateCompleted) {
        self.openButton.hidden = NO;
        self.downloadButton.hidden = YES;
        self.progressView.hidden = YES;
    } else if (info.state == DownloadStateWillResume) {
        self.openButton.hidden = YES;
        self.downloadButton.hidden = NO;
        self.progressView.hidden = NO;
        
        [self.downloadButton setBackgroundImage:[UIImage imageNamed:@"clock"] forState:UIControlStateNormal];
    } else {
        self.openButton.hidden = YES;
        self.downloadButton.hidden = NO;
        
        if (info.state == DownloadStateNone ) {
            self.progressView.hidden = YES;
        } else {
            self.progressView.hidden = NO;
            
            if (info.totalBytesExpectedToWrite) {
                self.progressView.progress = 1.0 * info.totalBytesWritten / info.totalBytesExpectedToWrite;
            } else {
                self.progressView.progress = 0.0;
            }
        }
        
        if (info.state == DownloadStateResumed) {
            [self.downloadButton setBackgroundImage:[UIImage imageNamed:@"pause"] forState:UIControlStateNormal];
        } else {
            [self.downloadButton setBackgroundImage:[UIImage imageNamed:@"download"] forState:UIControlStateNormal];
        }
    }
}

- (IBAction)download:(UIButton *)sender {
    DownloadInfo *info = [[DownloadManager defaultManager] downloadInfoForURL:self.url];
    
    if (info.state == DownloadStateResumed || info.state == DownloadStateWillResume) {
        [[DownloadManager defaultManager] suspend:info.url];
    } else {
        [[DownloadManager defaultManager] download:self.url progress:^(NSInteger bytesWritten, NSInteger totalBytesWritten, NSInteger totalBytesExpectedToWrite) {
            dispatch_async(dispatch_get_main_queue(), ^{
                self.url = self.url;
            });
        } state:^(DownloadState state, NSString *file, NSError *error) {
            dispatch_async(dispatch_get_main_queue(), ^{
                self.url = self.url;
            });
        }];
    }
}

- (IBAction)open:(UIButton *)sender {
    DownloadInfo *info = [[DownloadManager defaultManager] downloadInfoForURL:self.url];
    
    
    [self.delegate openMovieFile:info.file];
    /*
     UIViewController *vc = [UIApplication sharedApplication].keyWindow.rootViewController;
     
     
     MPMoviePlayerViewController *mpc = [[MPMoviePlayerViewController alloc] initWithContentURL:[NSURL fileURLWithPath:info.file]];
     NSLog(@"file = %@",info.file);
     [vc presentViewController:mpc animated:YES completion:nil];
     */
}

@end
