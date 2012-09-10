<div class="form">

<?php $form=$this->beginWidget('CActiveForm', array(
	'id'=>'admin-basic-info-form',
	'enableClientValidation'=>true,
	'enableAjaxValidation'=>false,
	'htmlOptions' => array('enctype' => 'multipart/form-data'),
)); ?>

	<p class="note"><?php
	echo InformationManagementModule::t('other','Fields with <span class="required">*</span> are required.'); /* no CHtml::encode here*/?></p>

	<?php echo $form->errorSummary(array($model,$personalInfoModel)); ?>

	<div class="row">
		<?php echo $form->labelEx($model,'admin_id'); ?>
		<?php echo $form->textField($model,'admin_id',array('size'=>10,'maxlength'=>10)); ?>
		<?php echo $form->error($model,'admin_id'); ?>
	</div>

	<?php echo $this->renderPartial('/personalInfo/_embeddedForm', array('personalInfoModel'=>$personalInfoModel,'form'=>$form)); 
	//so that every type of user can reuse this.
	?>

	<div class="row buttons">
		<?php echo CHtml::submitButton($model->isNewRecord ? Yii::t('base','Create'):Yii::t('base','Save')); ?>
	</div>

<?php $this->endWidget(); ?>

</div><!-- form -->