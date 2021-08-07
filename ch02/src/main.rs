use opencv::{
	highgui,
	imgcodecs,
    prelude::*,
    imgproc,
	Result,
};

fn display_caption(src: Mat, caption: String) -> i32
{
    let dst = Mat::zeros(512,512,opencv::core::CV_32F);
    return 0;
}

fn main() -> Result<()> {
	let image = imgcodecs::imread("Lenna.png", 0)?;
	highgui::named_window("hello opencv!", 0)?;
	highgui::imshow("hello opencv!", &image)?;
    highgui::named_window("hello opencv2!",0)?;
    let mut sz = image.size();

    // let mut dst = Mat::zeros(image.size().width, image.size().height,opencv::core::CV_32F);
    // opencv::imgproc::blur(&image, &mut dst,opencv::core::Size::new(1,1),opencv::core::Point::new(-1,-1), 1);
    // highgui::imshow("hello opencv2!",&image)?;
	highgui::wait_key(10000)?;
	Ok(())
}