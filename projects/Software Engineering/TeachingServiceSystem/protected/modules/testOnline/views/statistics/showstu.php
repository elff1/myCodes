<?php
$this->breadcrumbs=array(
		'Online Test Subsystem'=>array('/testOnline'),
		'Course List'=>array('default/listCourses'),
		AccountComponent::getSelected_course_name()=>array('paperBank/'),
		'Historical Performance',
		//显示学生成绩分析
);
	//用于列表显示内容
?>

<h1>Show students</h1>
<?php 
$dt1 =  TestInfoComponent::getStudentScore('45');
$dt = array();
$na = array();
$i = 0;
foreach ($dt1 as $key => $value) {
    $dt[$i] = $value;
    $na[$i] = $key;
    //echo $key;
    $i++;
	//echo "Key: $key; Value: $value<br />\n";
}
// 给一个stu的id，返回这个学生的array的成绩
// 绘制学生成绩折线图
$this ->Widget('ext.highcharts.HighchartsWidget', array(
       'options' => array(
		   
           'title' => array('text' => 'Your history of all your papers in '.AccountComponent::getSelected_course_name()),
           'xAxis' => array(
				'categories' => $na,
               'labels' => array(
                   'align' => 'right',
                   'style' => array(
                       'font' => 'normal 13px Verdana, sans-serif',
               )),
           ),
           'yAxis' => array(
               'min' => 0,
           	   'max' => 100,
               'title' => array('text' => 'scores')
           ),
           'legend' => array(
               'enabled' => false,
           ),
           'tooltip' => array(
               'formatter' => 'js:function() {
           return \'<STRONG>\'+ this.x +\'</STRONG>\'+
               \': \'+this.y +
               \'\';

     }' ),
           'series' => array(
               array(
                   'type' => 'line',
                   'data' => $dt,
                   'dataLabels' => $na,
               ),
           )
       )
   ));
 
?>
