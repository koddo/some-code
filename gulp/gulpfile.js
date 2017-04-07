var gulp = require('gulp'),
    watch = require('gulp-watch'),
    less = require('gulp-less'),
    plumber = require('gulp-plumber'),
    LessPluginCleanCSS = require('less-plugin-clean-css'),
    LessPluginAutoPrefix = require('less-plugin-autoprefix'),
    cleancss = new LessPluginCleanCSS({ advanced: true }),
    autoprefix = new LessPluginAutoPrefix({ browsers: ["last 2 versions"] });

var lesspath = './src/**/*.less';
var lessdest = './dest';

gulp.task('less', function() {
    return gulp.src(lesspath)
               .pipe(plumber())
               .pipe(less({plugins: [autoprefix, cleancss]}))
               .pipe(gulp.dest(lessdest));
});

gulp.task('watch', function() {
    gulp.watch(lesspath, ['less']);
});

gulp.task('default', ['less', 'watch']); // Default will run the 'entry' watch task

