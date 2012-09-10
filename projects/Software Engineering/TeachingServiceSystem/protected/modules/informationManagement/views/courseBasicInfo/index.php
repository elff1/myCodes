<?php
//顶部导航栏
$this->breadcrumbs=array(
	'Course Basic Infos',
);
//右侧菜单栏
$this->menu=array(
	array('label'=>'Create CourseBasicInfo', 'url'=>array('create')),
	array('label'=>'Manage CourseBasicInfo', 'url'=>array('admin')),
);
?>

<h1>Course Basic Infos</h1>
<!--显示数据表格的widget-->
<?php $this->widget('zii.widgets.CListView', array(
	'dataProvider'=>$dataProvider,
	'itemView'=>'_view',
)); ?>
