<?php
//顶部导航栏
$this->breadcrumbs=array(
	'Course Basic Infos'=>array('index'),
	'Create',
);
//右侧菜单栏
$this->menu=array(
	array('label'=>'List CourseBasicInfo', 'url'=>array('index')),
	array('label'=>'Manage CourseBasicInfo', 'url'=>array('admin')),
);
?>

<h1>Create CourseBasicInfo</h1>
<!--渲染数据表格-->
<?php echo $this->renderPartial('_form', array('model'=>$model)); ?>