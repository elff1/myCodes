<?php
//顶部导航栏
$this->breadcrumbs=array(
	'Program Details'=>array('index'),
	$model->id=>array('view','id'=>$model->id),
	'Update',
);

//右侧菜单栏
$this->menu=array(
	array('label'=>'List ProgramDetail', 'url'=>array('index')),
	array('label'=>'Create ProgramDetail', 'url'=>array('create')),
	array('label'=>'View ProgramDetail', 'url'=>array('view', 'id'=>$model->id)),
	array('label'=>'Manage ProgramDetail', 'url'=>array('admin')),
);
?>

<h1>Update ProgramDetail <?php echo $model->id; ?></h1>

<!--从_form.php加载并显示数据表格-->
<?php echo $this->renderPartial('_form', array('model'=>$model)); ?>