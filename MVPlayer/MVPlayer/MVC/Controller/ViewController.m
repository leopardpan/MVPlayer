//
//  ViewController.m
//  MVPlayer
//
//  Created by 潘柏信 on 15/9/24.
//  Copyright (c) 2015年 leopard. All rights reserved.
//

#import "ViewController.h"
#import "TableViewCell.h"
#import "Download.h"
#import "VideoPlayerController.h"
#import "DownloadManager.h"

@interface ViewController ()<CellDelegate>
@property (strong, nonatomic) NSMutableArray *urls;
@property (nonatomic, strong) VideoPlayerController *videoController;
@end

@implementation ViewController

- (IBAction)suspendAll:(id)sender {
    [[DownloadManager defaultManager] suspendAll];
}

- (IBAction)resumeAll:(id)sender {
    [[DownloadManager defaultManager] resumeAll];
}

- (NSMutableArray *)urls
{
    if (!_urls) {
        self.urls = [NSMutableArray array];
        for (int i = 1; i<=10; i++) {
            [self.urls addObject:[NSString stringWithFormat:@"http://120.25.226.186:32812/resources/videos/minion_%02d.mp4", i]];
            //            [self.urls addObject:[NSString stringWithFormat:@"http://localhost:8080/Server/resources/big_videos/%02d.mp4", i]];
        }
    }
    return _urls;
}

- (void)viewDidLoad {
    [super viewDidLoad];
    
    [DownloadManager defaultManager].maxDownloadingCount = 1;
}

#pragma mark - Table view data source
- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
    return self.urls.count;
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
    static NSString *ID = @"file";
    TableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:ID];
    cell.delegate = self;
    cell.url = self.urls[indexPath.row];
    return cell;
}

-(void)openMovieFile:(NSString *)file
{
    NSURL *url = [NSURL fileURLWithPath:file];
    if (!self.videoController) {
        
        CGFloat width = [UIScreen mainScreen].bounds.size.width;
        self.videoController = [[VideoPlayerController alloc] initWithFrame:CGRectMake(0, 64, width, 150)];
        __weak typeof(self)weakSelf = self;
        [self.videoController setDimissCompleteBlock:^{
            weakSelf.videoController = nil;
        }];
        [self.videoController showInWindow];
    }
    self.videoController.contentURL = url;
    
    
}
@end
